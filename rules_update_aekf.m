function rules_update_aekf()
% RULES_UPDATE_AEKF  2026 FS rules compliance updates inside Drive_AEKF:
%  1) motor CAN stale-data guard (500 ms, T12.10.2-d / T12.10.5)
%  2) released pedal / APPS fault -> zero wheel torque (T12.9.12 / T12.9.8)

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'rules_update_log.txt');

fid = fopen(outFile, 'w');
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));
    logicPath = Simulink.ID.getFullName([mdl ':546']);
    mf = [logicPath '/Drive_AEKF/aekf_comp'];
    rt = sfroot;
    chart = rt.find('-isa', 'Stateflow.EMChart', 'Path', mf);
    if isempty(chart)
        error('rules_update_aekf:chart', 'EMChart not found: %s', mf);
    end
    chart(1).Script = aekfCodeRules();
    w(sprintf('Script updated.'));

    save_system(mdl);
    w(sprintf('SAVE_OK'));

    close_system(mdl, 0);
    load_system(fullfile(srcDir, [mdl '.slx']));
    try
        set_param(mdl, 'SimulationCommand', 'update');
        w(sprintf('UPDATE_OK'));
    catch err
        w(sprintf('UPDATE_ERROR: %s', err.message));
    end
    close_system(mdl, 0);
    w(sprintf('RULES_UPDATE_DONE'));
catch err
    w(sprintf('RULES_UPDATE_ERROR'));
    w(getReport(err, 'extended'));
    try
        close_system(mdl, 0);
    catch %#ok<CTCH>
    end
end

end

function code = aekfCodeRules()
lines = {
'function T_opt = aekf_comp(T_base, w_rpm, Te_raw)'
'% Reduced-order AEKF + active damping (VCU 10 ms)'
'% 2026 FS rules: T12.9.12 released pedal -> 0 torque; T12.10.5 CAN stale 500 ms'
'persistent x1 x2 P11 P12 P22 lam bad_t good_t comp_g buf idx sum_nis ff_lp'
'persistent w_prev Te_prev stale_cnt'
'if isempty(x1)'
'    x1 = 0.0; x2 = 0.0;'
'    P11 = 100.0; P12 = 0.0; P22 = 25.0;'
'    lam = 0.98; bad_t = 0.0; good_t = 0.0; comp_g = 1.0;'
'    buf = zeros(10,1); idx = 1; sum_nis = 0.0; ff_lp = 0.0;'
'    w_prev = 0.0; Te_prev = 0.0; stale_cnt = 0;'
'end'
'Ts = 0.01; J = 0.003; B = 5.0e-4;'
'Q1 = 1.0e-3; Q2 = 1.0; R = 0.01;'
'lam_max = 0.98; lam_min = 0.85; gam = 3.841; aa = 0.5;'
'Pcap1 = 100.0; Pcap2 = 400.0;'
'Kd = 0.01; WFF = 2.0*pi*5.0; FFMAX = 6.0; RAW = 10.0;'
'w = w_rpm*(2.0*pi/60.0);'
'Te = Te_raw/RAW;'
'% stale CAN guard: no change for 50 cycles = 500 ms'
'if (w_rpm == w_prev) && (Te_raw == Te_prev)'
'    stale_cnt = stale_cnt + 1;'
'else'
'    stale_cnt = 0;'
'end'
'w_prev = w_rpm; Te_prev = Te_raw;'
'stale = stale_cnt >= 50;'
'if ~stale'
'    % predict'
'    f1 = (Te - x2 - B*x1)/J;'
'    x1p = x1 + Ts*f1; x2p = x2;'
'    F11 = 1.0 - Ts*B/J; F12 = -Ts/J; F22 = 1.0;'
'    Pp11 = F11*(F11*P11 + F12*P12) + F12*(F11*P12 + F12*P22) + Q1;'
'    Pp12 = F11*P12 + F12*P22;'
'    Pp22 = P22 + Q2;'
'    % innovation and NIS'
'    eps = w - x1p;'
'    S = Pp11 + R;'
'    nis = (eps*eps)/S;'
'    sum_nis = sum_nis - buf(idx) + nis;'
'    buf(idx) = nis;'
'    idx = idx + 1;'
'    if idx > 10'
'        idx = 1;'
'    end'
'    nb = sum_nis/10.0;'
'    % adaptive forgetting factor'
'    arg = aa*(nb - gam);'
'    if arg > 50.0'
'        arg = 50.0;'
'    elseif arg < -50.0'
'        arg = -50.0;'
'    end'
'    lam = lam_min + (lam_max - lam_min)/(1.0 + exp(arg));'
'    if nb > gam'
'        Pp11 = Pp11/lam; Pp12 = Pp12/lam; Pp22 = Pp22/lam;'
'    end'
'    if Pp11 > Pcap1'
'        Pp11 = Pcap1;'
'    end'
'    if Pp22 > Pcap2'
'        Pp22 = Pcap2;'
'    end'
'    S = Pp11 + R;'
'    K1 = Pp11/S; K2 = Pp12/S;'
'    x1 = x1p + K1*eps; x2 = x2p + K2*eps;'
'    % Joseph covariance update'
'    IK11 = 1.0 - K1; IK21 = -K2; IK22 = 1.0;'
'    A11 = IK11*Pp11; A12 = IK11*Pp12;'
'    A21 = IK21*Pp11 + Pp12; A22 = IK21*Pp12 + Pp22;'
'    P11 = A11*IK11 + (K1*K1)*R;'
'    P12 = A11*IK21 + A12*IK22 + K1*K2*R;'
'    P22 = A21*IK21 + A22*IK22 + (K2*K2)*R;'
'    % fault-safe: fade out after 20 ms, recover after 50 ms'
'    if nb > gam'
'        bad_t = bad_t + Ts; good_t = 0.0;'
'    else'
'        good_t = good_t + Ts;'
'        if good_t > 0.05'
'            bad_t = 0.0;'
'        end'
'    end'
'    if bad_t > 0.02'
'        tgt = 0.0;'
'    else'
'        tgt = 1.0;'
'    end'
'    comp_g = comp_g + (tgt - comp_g)*Ts/0.01;'
'    % feedforward: low-pass + limit + gate'
'    ff_lp = ff_lp + Ts*WFF*(x2 - ff_lp);'
'    ff = ff_lp;'
'    if ff > FFMAX'
'        ff = FFMAX;'
'    elseif ff < -FFMAX'
'        ff = -FFMAX;'
'    end'
'    ff = ff*comp_g;'
'    % active damping'
'    damp = Kd*x1;'
'else'
'    % CAN stale: freeze estimator, disable feedforward and damping'
'    ff = 0.0; damp = 0.0; comp_g = 0.0;'
'end'
'% compose command in raw units'
'T_opt = T_base + (ff - damp)*RAW;'
'% T12.9.12 / T12.9.8: released pedal or APPS fault -> zero drive torque'
'if T_base <= 0.0'
'    T_opt = 0.0;'
'elseif T_opt < 0.0'
'    T_opt = 0.0;'
'elseif T_opt > 5000.0'
'    T_opt = 5000.0;'
'end'
'end'
};
code = strjoin(lines.', sprintf('\n'));
end
