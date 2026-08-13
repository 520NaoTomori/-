function analyze_text28()
% ANALYZE_TEXT28  Load text28.slx and dump a structural analysis report.
%   Intended to run under MATLAB R2014a in -nodesktop mode.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'text28_analysis.txt');

fid = fopen(outFile, 'w');
if fid < 0
    error('analyze_text28:open', 'Cannot open report file: %s', outFile);
end
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    % ---------------- Load ----------------
    w(sprintf('=== LOAD ==='));
    load_system(fullfile(srcDir, [mdl '.slx']));
    w(sprintf('LOAD_OK'));
    w(sprintf('ModelVersion      : %s', safeGet(mdl, 'ModelVersion')));
    w(sprintf('LastModifiedBy    : %s', safeGet(mdl, 'LastModifiedBy')));
    w(sprintf('Description       : %s', safeGet(mdl, 'Description')));
    w(sprintf('SimulationMode    : %s', safeGet(mdl, 'SimulationMode')));
    w(sprintf('SolverType        : %s', safeGet(mdl, 'SolverType')));
    w(sprintf('Solver            : %s', safeGet(mdl, 'Solver')));
    w(sprintf('StopTime          : %s', safeGet(mdl, 'StopTime')));
    w(sprintf('MaxStep           : %s', safeGet(mdl, 'MaxStep')));
    w(sprintf('FixedStep         : %s', safeGet(mdl, 'FixedStep')));
    w(sprintf('AbsTol            : %s', safeGet(mdl, 'AbsTol')));
    w(sprintf('RelTol            : %s', safeGet(mdl, 'RelTol')));

    % ---------------- Block census ----------------
    w(sprintf(''));
    w(sprintf('=== BLOCK CENSUS (all levels) ==='));
    blocks = find_system(mdl, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'Type', 'block');
    blocks(cellfun(@(b) strcmp(b, mdl), blocks)) = [];
    nBlocks = numel(blocks);
    w(sprintf('TotalBlocks       : %d', nBlocks));

    types = containers.Map();
    for i = 1:nBlocks
        try
            t = get_param(blocks{i}, 'BlockType');
        catch %#ok<CTCH>
            t = 'Unknown';
        end
        if types.isKey(t)
            types(t) = types(t) + 1;
        else
            types(t) = 1;
        end
    end
    keysAll = types.keys;
    valsAll = cell2mat(types.values);
    [~, ord] = sort(valsAll, 'descend');
    for i = 1:numel(ord)
        k = keysAll{ord(i)};
        w(sprintf('  %-28s : %5d', k, types(k)));
    end

    % ---------------- Top level ----------------
    w(sprintf(''));
    w(sprintf('=== TOP-LEVEL ==='));
    top = find_system(mdl, 'SearchDepth', 1, 'Type', 'block');
    top(cellfun(@(b) strcmp(b, mdl), top)) = [];
    w(sprintf('TopLevelBlocks    : %d', numel(top)));
    for i = 1:numel(top)
        b = top{i};
        try
            bt = get_param(b, 'BlockType');
            ports = mat2str(get_param(b, 'Ports'));
        catch %#ok<CTCH>
            bt = 'Unknown';
            ports = 'n/a';
        end
        w(sprintf('  [%d] %s | %s | Ports=%s', i, b, bt, ports));
    end

    % ---------------- I/O ----------------
    inports = find_system(mdl, 'SearchDepth', 1, 'BlockType', 'Inport');
    outports = find_system(mdl, 'SearchDepth', 1, 'BlockType', 'Outport');
    w(sprintf(''));
    w(sprintf('Inports           : %d', numel(inports)));
    for i = 1:numel(inports)
        w(sprintf('  %s | Port=%s | DataType=%s', inports{i}, ...
            safeGet(inports{i}, 'Port'), safeGet(inports{i}, 'OutDataTypeStr')));
    end
    w(sprintf('Outports          : %d', numel(outports)));
    for i = 1:numel(outports)
        w(sprintf('  %s | Port=%s | DataType=%s', outports{i}, ...
            safeGet(outports{i}, 'Port'), safeGet(outports{i}, 'OutDataTypeStr')));
    end

    % ---------------- Subsystems ----------------
    subs = find_system(mdl, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'BlockType', 'SubSystem');
    w(sprintf(''));
    w(sprintf('Subsystems        : %d', numel(subs)));
    for i = 1:numel(subs)
        try
            mt = get_param(subs{i}, 'MaskType');
            if isempty(mt)
                mt = '(none)';
            end
        catch %#ok<CTCH>
            mt = '(none)';
        end
        w(sprintf('  %s | Mask=%s', subs{i}, mt));
    end

    % ---------------- Stateflow / Data stores / lines ----------------
    try
        sfCharts = find_system(mdl, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'MaskType', 'Stateflow');
        w(sprintf(''));
        w(sprintf('StateflowCharts   : %d', numel(sfCharts)));
    catch %#ok<CTCH>
        w(sprintf('StateflowCharts   : n/a'));
    end
    try
        dsm = find_system(mdl, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'BlockType', 'DataStoreMemory');
        w(sprintf('DataStoreMem      : %d', numel(dsm)));
        for i = 1:numel(dsm)
            w(sprintf('  %s | Name=%s', dsm{i}, safeGet(dsm{i}, 'DataStoreName')));
        end
    catch %#ok<CTCH>
        w(sprintf('DataStoreMem      : n/a'));
    end
    try
        allLines = find_system(mdl, 'FindAll', 'on', 'Type', 'line');
        w(sprintf('Lines(all)        : %d', numel(allLines)));
        topLines = find_system(mdl, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
        w(sprintf('Lines(top-level)  : %d', numel(topLines)));
    catch %#ok<CTCH>
        w(sprintf('Lines             : n/a'));
    end

    % ---------------- Model workspace ----------------
    try
        mw = get_param(mdl, 'ModelWorkspace');
        vars = mw.whos;
        w(sprintf(''));
        w(sprintf('=== MODEL WORKSPACE (%d vars) ===', numel(vars)));
        for i = 1:numel(vars)
            w(sprintf('  %-24s %8s x %s', vars(i).name, mat2str(vars(i).size), vars(i).class));
        end
    catch err
        w(sprintf('ModelWorkspace    : <error %s>', err.message));
    end

    w(sprintf(''));
    w(sprintf('ANALYSIS_DONE'));

    close_system(mdl, 0);
catch err
    w(sprintf(''));
    w(sprintf('ANALYSIS_ERROR'));
    w(getReport(err, 'extended'));
    try
        close_system(mdl, 0);
    catch %#ok<CTCH>
    end
end

end

function s = safeGet(pathOrHandle, prop)
% SAFEGET  Return a parameter value or a readable error string.
try
    v = get_param(pathOrHandle, prop);
    if ischar(v)
        s = v;
    elseif isnumeric(v)
        s = mat2str(v);
    else
        s = class(v);
    end
catch err
    s = sprintf('<n/a: %s>', err.message);
end
end
