function verify_cleanup()
% VERIFY_CLEANUP  Check drive logic outports, dead-code removal, AEKF wiring.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'verify_cleanup.txt');

fid = fopen(outFile, 'w');
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));

    logicPath = Simulink.ID.getFullName([mdl ':546']);
    drivePath = Simulink.ID.getFullName([mdl ':2']);
    w(sprintf('logicPath=%s', logicPath));
    w(sprintf('drivePath=%s', drivePath));

    w(sprintf('-- drive logic outports:'));
    outs = find_system(logicPath, 'SearchDepth', 1, 'BlockType', 'Outport');
    for i = 1:numel(outs)
        try
            w(sprintf('  port %s : %s', mat2str(get_param(outs{i}, 'Port')), get_param(outs{i}, 'Name')));
        catch %#ok<CTCH>
        end
    end

    w(sprintf('-- dead blocks present (expect 0):'));
    deadSids = [1011, 1977, 1961, 1971];
    for k = 1:numel(deadSids)
        try
            p = Simulink.ID.getFullName([mdl ':' num2str(deadSids(k))]);
            w(sprintf('  sid %d : PRESENT (%s)', deadSids(k), p));
        catch %#ok<CTCH>
            w(sprintf('  sid %d : absent', deadSids(k)));
        end
    end

    w(sprintf('-- motor speed subsystem:'));
    motorPath = Simulink.ID.getFullName([mdl ':1816']);
    outs2 = find_system(motorPath, 'SearchDepth', 1, 'BlockType', 'Outport');
    for i = 1:numel(outs2)
        try
            w(sprintf('  port %s : %s', mat2str(get_param(outs2{i}, 'Port')), get_param(outs2{i}, 'Name')));
        catch %#ok<CTCH>
        end
    end

    w(sprintf('-- Drive_AEKF:'));
    aekf = find_system(logicPath, 'SearchDepth', 1, 'Name', 'Drive_AEKF');
    if ~isempty(aekf)
        w(sprintf('  found: %s', aekf{1}));
        ins = find_system(aekf{1}, 'SearchDepth', 1, 'BlockType', 'Inport');
        for i = 1:numel(ins)
            w(sprintf('  in port %s : %s', mat2str(get_param(ins{i}, 'Port')), get_param(ins{i}, 'Name')));
        end
        outs3 = find_system(aekf{1}, 'SearchDepth', 1, 'BlockType', 'Outport');
        for i = 1:numel(outs3)
            w(sprintf('  out port %s : %s', mat2str(get_param(outs3{i}, 'Port')), get_param(outs3{i}, 'Name')));
        end
    else
        w(sprintf('  NOT FOUND'));
    end

    w(sprintf('VERIFY_DONE'));
    close_system(mdl, 0);
catch err
    w(sprintf('VERIFY_ERROR'));
    w(getReport(err, 'extended'));
    try
        close_system(mdl, 0);
    catch %#ok<CTCH>
    end
end

end
