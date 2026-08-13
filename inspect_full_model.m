function inspect_full_model()
% INSPECT_FULL_MODEL  Full-model audit: block tree, key parameters, lines,
% and usage tracing of BMS/MCU CAN signals. Writes UTF-8 report.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'full_model_audit.txt');

fid = fopen(outFile, 'w');
if fid < 0
    error('inspect:open', 'Cannot open %s', outFile);
end
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));
    w(sprintf('LOAD_OK  %s', version));

    % ---------- 1. Full block census with key parameters ----------
    w(sprintf(''));
    w(sprintf('=== 1. FULL BLOCK TREE ==='));
    allBlk = find_system(mdl, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'Type', 'block');
    allBlk(cellfun(@(b) strcmp(b, mdl), allBlk)) = [];
    for i = 1:numel(allBlk)
        b = allBlk{i};
        bt = safeGet(b, 'BlockType');
        if strcmp(bt, 'SubSystem')
            extra = ' [SUB]';
        else
            extra = '';
        end
        w(sprintf('%s | %s%s', oneLine(b), bt, extra));
    end

    % ---------- 2. One-level lines per subsystem ----------
    w(sprintf(''));
    w(sprintf('=== 2. LINE DUMP (one level per subsystem) ==='));
    subs = find_system(mdl, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'BlockType', 'SubSystem');
    scopes = [{mdl}; subs];
    for s = 1:numel(scopes)
        sc = scopes{s};
        w(sprintf('-- %s', oneLine(sc)));
        dumpLines(fid, sc);
    end

    % ---------- 3. Key parameter values ----------
    w(sprintf(''));
    w(sprintf('=== 3. KEY PARAMETERS ==='));
    for i = 1:numel(allBlk)
        b = allBlk{i};
        bt = safeGet(b, 'BlockType');
        params = {};
        switch bt
            case 'Constant'
                params = {'Value', 'OutDataTypeStr'};
            case 'Gain'
                params = {'Gain', 'Multiplication', 'OutDataTypeStr'};
            case 'Saturation'
                params = {'UpperLimit', 'LowerLimit'};
            case 'UnitDelay'
                params = {'InitialCondition', 'SampleTime'};
            case 'Sum'
                params = {'Inputs'};
            case 'Switch'
                params = {'Criteria', 'Threshold', 'Inputs'};
            case 'RelationalOperator'
                params = {'Operator'};
            case 'LogicalOperator'
                params = {'Operator', 'Inputs'};
            case 'DataTypeConversion'
                params = {'OutDataTypeStr'};
            case 'S-Function'
                params = {'FunctionName', 'Parameters'};
            case 'If'
                params = {'IfExpression', 'ElseIfExpressions', 'ShowElse'};
        end
        if isempty(params), continue; end
        vals = '';
        for p = 1:numel(params)
            v = safeGet(b, params{p});
            if strcmp(v, '<n/a>'), continue; end
            vals = [vals params{p} '=' v '; ']; %#ok<AGROW>
        end
        if ~isempty(vals)
            w(sprintf('%s | %s', oneLine(b), vals));
        end
    end

    % ---------- 4. Trace BMS/MCU signal usage ----------
    w(sprintf(''));
    w(sprintf('=== 4. BMS / MCU CAN SIGNAL USAGE ==='));
    keys = {'BMS_HCU_INFO', 'MCU_STATUS_2', 'BatSoc', 'BatVoltage', 'BatCurrent', ...
            'BatState', 'BatAlmLv', 'MCU_temperature', 'Motor_Temperature', ...
            'Torque_Limit', 'Live_counter', 'Fail_Grade'};
    for k = 1:numel(keys)
        pat = keys{k};
    hits = find_system(mdl, 'LookUnderMasks', 'all', 'FollowLinks', 'on', ...
        'RegExp', 'on', 'Name', pat);
    hits2 = find_system(mdl, 'LookUnderMasks', 'all', 'FollowLinks', 'on', ...
        'RegExp', 'on', 'Description', pat);
        w(sprintf('-- pattern: %s (%d name hits, %d desc hits)', pat, numel(hits), numel(hits2)));
        for h = 1:numel(hits)
            w(sprintf('    %s | %s', oneLine(hits{h}), safeGet(hits{h}, 'BlockType')));
        end
        for h = 1:numel(hits2)
            w(sprintf('    DESC %s | %s', oneLine(hits2{h}), safeGet(hits2{h}, 'BlockType')));
        end
    end

    w(sprintf(''));
    w(sprintf('AUDIT_DONE'));
    close_system(mdl, 0);
catch err
    w(sprintf('AUDIT_ERROR'));
    w(getReport(err, 'extended'));
    try
        close_system(mdl, 0);
    catch %#ok<CTCH>
    end
end

end

function dumpLines(fid, sysPath)
w = @(s) fprintf(fid, '%s\n', s);
lines = find_system(sysPath, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
for i = 1:numel(lines)
    lh = lines(i);
    try
        nm = get_param(lh, 'Name');
        if iscell(nm)
            if isempty(nm), nm = ''; else nm = nm{1}; end
        end
        if isempty(nm), nm = '(unnamed)'; end
    catch %#ok<CTCH>
        nm = '(unnamed)';
    end
    try
        srcB = oneLine(strrep(char(getfullname(get_param(lh, 'SrcBlockHandle'))), [sysPath '/'], ''));
        srcP = num2str(get_param(get_param(lh, 'SrcPortHandle'), 'PortNumber'));
    catch %#ok<CTCH>
        srcB = '?'; srcP = '?';
    end
    try
        dstB = oneLine(strrep(char(getfullname(get_param(lh, 'DstBlockHandle'))), [sysPath '/'], ''));
        dstP = num2str(get_param(get_param(lh, 'DstPortHandle'), 'PortNumber'));
    catch %#ok<CTCH>
        dstB = '?'; dstP = '?';
    end
    w(sprintf('    "%s" : %s:%s -> %s:%s', nm, srcB, srcP, dstB, dstP));
end
end

function s = safeGet(pathOrHandle, prop)
try
    v = get_param(pathOrHandle, prop);
    if ischar(v)
        s = v;
    elseif isnumeric(v)
        s = mat2str(v);
    else
        s = class(v);
    end
catch %#ok<CTCH>
    s = '<n/a>';
end
end

function s = oneLine(v)
s = char(v);
s = strrep(s, sprintf('\n'), '|');
s = strrep(s, sprintf('\r'), '');
end
