function integrate_aekf()
% INTEGRATE_AEKF  Replace wheel-speed-based Drive_TCS with a reduced-order
% AEKF disturbance estimator + active damping (paper-based, no extra sensors).
% Works on the copied model only; R2014a compatible.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'integrate_log.txt');

fid = fopen(outFile, 'w');
if fid < 0
    error('integrate_aekf:open', 'Cannot open log file: %s', outFile);
end
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));

    drivePath = Simulink.ID.getFullName([mdl ':2']);
    logicPath = Simulink.ID.getFullName([mdl ':546']);
    appsOut   = Simulink.ID.getFullName([mdl ':921']);
    thrOut    = Simulink.ID.getFullName([mdl ':581']);
    rearSrc   = Simulink.ID.getFullName([mdl ':1816']);
    tcs       = [logicPath '/Drive_TCS'];

    % ---- Log drive trigger source (task rate) ----
    rootLines = find_system(mdl, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
    demuxPath = '';
    for i = 1:numel(rootLines)
        try
            dstB = getfullname(get_param(rootLines(i), 'DstBlockHandle'));
            if strcmp(dstB, drivePath)
                srcB = getfullname(get_param(rootLines(i), 'SrcBlockHandle'));
                try
                    fn = get_param(srcB, 'FunctionName');
                catch %#ok<CTCH>
                    fn = srcB;
                end
                w(sprintf('DRIVE_TRIGGER_SRC=%s (%s)', srcB, fn));
                demuxPath = srcB;
            end
        catch %#ok<CTCH>
        end
    end
    if ~isempty(demuxPath)
        for i = 1:numel(rootLines)
            try
                dstB = getfullname(get_param(rootLines(i), 'DstBlockHandle'));
                if strcmp(dstB, demuxPath)
                    srcB = getfullname(get_param(rootLines(i), 'SrcBlockHandle'));
                    try
                        fn = get_param(srcB, 'FunctionName');
                    catch %#ok<CTCH>
                        fn = srcB;
                    end
                    w(sprintf('DEMUX_SRC=%s (%s)', srcB, fn));
                end
            catch %#ok<CTCH>
            end
        end
    end

    % ---- Remove old wheel-speed Drive_TCS ----
    if ~isempty(find_system(logicPath, 'SearchDepth', 1, 'Name', 'Drive_TCS'))
        lines = find_system(logicPath, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
        for i = 1:numel(lines)
            try
                srcB = getfullname(get_param(lines(i), 'SrcBlockHandle'));
                dstB = getfullname(get_param(lines(i), 'DstBlockHandle'));
            catch %#ok<CTCH>
                continue;
            end
            if strcmp(srcB, tcs) || strcmp(dstB, tcs)
                delete_line(lines(i));
            end
        end
        delete_block(tcs);
        w(sprintf('REMOVED %s', tcs));
    end

    % ---- Create Drive_AEKF subsystem ----
    aekf = [logicPath '/Drive_AEKF'];
    add_block('built-in/Subsystem', aekf, 'Position', [600 60 820 340]);
    w(sprintf('Created %s', aekf));

    add_block('built-in/Inport', [aekf '/T_base'], 'Position', [30 60 60 74]);
    add_block('built-in/Inport', [aekf '/w_rpm'],  'Position', [30 140 60 154]);
    add_block('built-in/Inport', [aekf '/Te_raw'], 'Position', [30 220 60 234]);
    add_block('built-in/Outport', [aekf '/T_opt'], 'Position', [680 150 710 164]);

    add_block('built-in/DataTypeConversion', [aekf '/T_base_d'], 'Position', [90 55 140 79], 'OutDataTypeStr', 'double');
    add_block('built-in/DataTypeConversion', [aekf '/w_rpm_d'],  'Position', [90 135 140 159], 'OutDataTypeStr', 'double');
    add_block('built-in/DataTypeConversion', [aekf '/Te_raw_d'], 'Position', [90 215 140 239], 'OutDataTypeStr', 'double');

    % ---- MATLAB Function block with the AEKF algorithm ----
    mf = [aekf '/aekf_comp'];
    add_block('simulink/User-Defined Functions/MATLAB Function', mf, 'Position', [180 60 420 260]);
    rt = sfroot;
    chart = [];
    try
        chart = rt.find('-isa', 'Stateflow.EMChart', 'Path', mf);
    catch %#ok<CTCH>
    end
    if isempty(chart)
        set_param(mdl, 'SimulationCommand', 'update');
        chart = rt.find('-isa', 'Stateflow.EMChart', 'Path', mf);
    end
    if isempty(chart)
        error('integrate_aekf:chart', 'EMChart not found for %s', mf);
    end
    chart(1).Script = aekfCode();
    w(sprintf('AEKF script installed.'));

    % ---- Output rate limiter (unit-delay based, 10 ms step) ----
    add_block('built-in/UnitDelay', [aekf '/TorquePrev'], 'InitialCondition', '0', 'SampleTime', '-1', 'Position', [520 240 570 260]);
    add_block('built-in/Sum', [aekf '/TorqueDelta'], 'Inputs', '+-', 'Position', [480 130 510 160]);
    add_block('built-in/Saturation', [aekf '/TorqueDeltaSat'], 'UpperLimit', '25', 'LowerLimit', '-50', 'Position', [540 130 590 160]);
    add_block('built-in/Sum', [aekf '/TorqueSum'], 'Inputs', '++', 'Position', [620 130 650 160]);

    % ---- Wire inside Drive_AEKF ----
    addLine2(aekf, 'T_base/1', 'T_base_d/1');
    addLine2(aekf, 'w_rpm/1',  'w_rpm_d/1');
    addLine2(aekf, 'Te_raw/1', 'Te_raw_d/1');
    addLine2(aekf, 'T_base_d/1','aekf_comp/1');
    addLine2(aekf, 'w_rpm_d/1', 'aekf_comp/2');
    addLine2(aekf, 'Te_raw_d/1','aekf_comp/3');
    addLine2(aekf, 'aekf_comp/1','TorqueDelta/1');
    addLine2(aekf, 'TorquePrev/1','TorqueDelta/2');
    addLine2(aekf, 'TorqueDelta/1','TorqueDeltaSat/1');
    addLine2(aekf, 'TorqueDeltaSat/1','TorqueSum/2');
    addLine2(aekf, 'TorquePrev/1','TorqueSum/1');
    addLine2(aekf, 'TorqueSum/1','T_opt/1');
    addLine2(aekf, 'TorqueSum/1','TorquePrev/1');
    w(sprintf('Drive_AEKF wired (%d lines).', numel(find_system(aekf, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line'))));

    % ---- Rewire at Subsystem level ----
    appsShort = get_param(appsOut, 'Name');
    thrShort  = get_param(thrOut, 'Name');
    rearShort = get_param(rearSrc, 'Name');
    addLine2(logicPath, [appsShort '/1'], 'Drive_AEKF/1');
    addLine2(logicPath, 'Drive_AEKF/1', [thrShort '/1']);
    addLine2(logicPath, [rearShort '/2'], 'Drive_AEKF/2');
    addLine2(logicPath, [rearShort '/3'], 'Drive_AEKF/3');
    w(sprintf('Subsystem rewired.'));

    % ---- Save ----
    save_system(mdl);
    w(sprintf('SAVE_OK'));

    % ---- Verify ----
    close_system(mdl, 0);
    load_system(fullfile(srcDir, [mdl '.slx']));
    aekf2 = [Simulink.ID.getFullName([mdl ':546']) '/Drive_AEKF'];
    nLines = numel(find_system(aekf2, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line'));
    nBlks  = numel(find_system(aekf2, 'SearchDepth', 1, 'Type', 'block'));
    w(sprintf('VERIFY Drive_AEKF blocks=%d lines=%d', nBlks, nLines));
    try
        set_param(mdl, 'SimulationCommand', 'update');
        w(sprintf('UPDATE_OK'));
    catch err
        w(sprintf('UPDATE_ERROR: %s', err.message));
    end
    close_system(mdl, 0);
    w(sprintf('INTEGRATE_DONE'));
catch err
    w(sprintf('INTEGRATE_ERROR'));
    w(getReport(err, 'extended'));
    try
        close_system(mdl, 0);
    catch %#ok<CTCH>
    end
end

end

function code = aekfCode()
% AEKFCODE  Reduced-order AEKF (states: w_hat, Td_hat) + active damping.
% Adapted from the author's paper / sim_3_6.m to a 10 ms VCU task using only
% motor speed (rpm) and motor torque (raw 0.1 Nm/LSB) CAN feedback.
lines = {
'function T_opt = aekf_comp(T_base, w_rpm, Te_raw)'
'% Reduced-order AEKF disturbance estimator + active damping (VCU 10 ms)'
'% T_base/T_opt: raw torque units (0.1 Nm/LSB); w_rpm: rpm; Te_raw: 0.1 Nm/LSB'
'persistent x1 x2 P11 P12 P22 lam bad_t good_t comp_g buf idx sum_nis ff_lp'
'if isempty(x1)'
'    x1 = 0.0; x2 = 0.0;'
'    P11 = 100.0; P12 = 0.0; P22 = 25.0;'
'    lam = 0.98; bad_t = 0.0; good_t = 0.0; comp_g = 1.0;'
'    buf = zeros(10,1); idx = 1; sum_nis = 0.0; ff_lp = 0.0;'
'end'
'Ts = 0.01; J = 0.003; B = 5.0e-4;'
'Q1 = 1.0e-3; Q2 = 1.0; R = 0.01;'
'lam_max = 0.98; lam_min = 0.85; gam = 3.841; aa = 0.5;'
'Pcap1 = 100.0; Pcap2 = 400.0;'
'Kd = 0.01; WFF = 2.0*pi*5.0; FFMAX = 6.0; RAW = 10.0;'
'w = w_rpm*(2.0*pi/60.0);'
'Te = Te_raw/RAW;'
'% predict'
'f1 = (Te - x2 - B*x1)/J;'
'x1p = x1 + Ts*f1; x2p = x2;'
'F11 = 1.0 - Ts*B/J; F12 = -Ts/J; F22 = 1.0;'
'Pp11 = F11*(F11*P11 + F12*P12) + F12*(F11*P12 + F12*P22) + Q1;'
'Pp12 = F11*P12 + F12*P22;'
'Pp22 = P22 + Q2;'
'% innovation and NIS'
'eps = w - x1p;'
'S = Pp11 + R;'
'nis = (eps*eps)/S;'
'sum_nis = sum_nis - buf(idx) + nis;'
'buf(idx) = nis;'
'idx = idx + 1;'
'if idx > 10'
'    idx = 1;'
'end'
'nb = sum_nis/10.0;'
'% adaptive forgetting factor'
'arg = aa*(nb - gam);'
'if arg > 50.0'
'    arg = 50.0;'
'elseif arg < -50.0'
'    arg = -50.0;'
'end'
'lam = lam_min + (lam_max - lam_min)/(1.0 + exp(arg));'
'if nb > gam'
'    Pp11 = Pp11/lam; Pp12 = Pp12/lam; Pp22 = Pp22/lam;'
'end'
'if Pp11 > Pcap1'
'    Pp11 = Pcap1;'
'end'
'if Pp22 > Pcap2'
'    Pp22 = Pcap2;'
'end'
'S = Pp11 + R;'
'K1 = Pp11/S; K2 = Pp12/S;'
'x1 = x1p + K1*eps; x2 = x2p + K2*eps;'
'% Joseph covariance update'
'IK11 = 1.0 - K1; IK21 = -K2; IK22 = 1.0;'
'A11 = IK11*Pp11; A12 = IK11*Pp12;'
'A21 = IK21*Pp11 + Pp12; A22 = IK21*Pp12 + Pp22;'
'P11 = A11*IK11 + (K1*K1)*R;'
'P12 = A11*IK21 + A12*IK22 + K1*K2*R;'
'P22 = A21*IK21 + A22*IK22 + (K2*K2)*R;'
'% fault-safe: fade out after 20 ms, recover after 50 ms'
'if nb > gam'
'    bad_t = bad_t + Ts; good_t = 0.0;'
'else'
'    good_t = good_t + Ts;'
'    if good_t > 0.05'
'        bad_t = 0.0;'
'    end'
'end'
'if bad_t > 0.02'
'    tgt = 0.0;'
'else'
'    tgt = 1.0;'
'end'
'comp_g = comp_g + (tgt - comp_g)*Ts/0.01;'
'% feedforward: low-pass + limit + gate'
'ff_lp = ff_lp + Ts*WFF*(x2 - ff_lp);'
'ff = ff_lp;'
'if ff > FFMAX'
'    ff = FFMAX;'
'elseif ff < -FFMAX'
'    ff = -FFMAX;'
'end'
'ff = ff*comp_g;'
'% active damping'
'damp = Kd*x1;'
'% compose command in raw units'
'T_opt = T_base + (ff - damp)*RAW;'
'if T_opt < 0.0'
'    T_opt = 0.0;'
'elseif T_opt > 5000.0'
'    T_opt = 5000.0;'
'end'
'end'
};
code = strjoin(lines.', sprintf('\n'));
end

function addLine2(sys, src, dst)
add_line(sys, src, dst, 'autorouting', 'on');
end
