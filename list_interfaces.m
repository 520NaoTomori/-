function list_interfaces()
% LIST_INTERFACES  Dump interfaces (ports + signal lines) of the ORIGINAL
% text28 model. Run against a pristine copy of E42\E42\text28.slx.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'interfaces.txt');

fid = fopen(outFile, 'w');
if fid < 0
    error('list_interfaces:open', 'Cannot open report file: %s', outFile);
end
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));

    % ================= 1. Root level =================
    w(sprintf('=== 1. ROOT LEVEL BLOCKS ==='));
    rootBlks = find_system(mdl, 'SearchDepth', 1, 'Type', 'block');
    rootBlks(cellfun(@(b) strcmp(b, mdl), rootBlks)) = [];
    for i = 1:numel(rootBlks)
        b = rootBlks{i};
        try
            bt = get_param(b, 'BlockType');
        catch %#ok<CTCH>
            bt = '?';
        end
        extra = '';
        if strcmp(bt, 'S-Function')
            try
                extra = [' FunctionName=' get_param(b, 'FunctionName')];
            catch %#ok<CTCH>
            end
        end
        try
            ports = mat2str(get_param(b, 'Ports'));
        catch %#ok<CTCH>
            ports = '?';
        end
        w(sprintf('  %s | %s | Ports=%s%s', b, bt, ports, extra));
    end

    w(sprintf(''));
    w(sprintf('=== 1b. ROOT LINES ==='));
    dumpLines(fid, mdl, mdl);

    % ================= 2. Drive subsystem interface =================
    drivePath = Simulink.ID.getFullName([mdl ':2']);
    logicPath = Simulink.ID.getFullName([mdl ':546']);
    w(sprintf(''));
    w(sprintf('=== 2. DRIVE INTERFACE ==='));
    w(sprintf('  drivePath=%s', drivePath));
    w(sprintf('  logicPath=%s', logicPath));

    % 2a. drive top-level lines
    w(sprintf('  -- drive top-level lines:'));
    dumpLines(fid, drivePath, drivePath);

    % 2b. drive logic subsystem outports
    w(sprintf('  -- Subsystem (drive logic) outports:'));
    outs = find_system(logicPath, 'SearchDepth', 1, 'BlockType', 'Outport');
    for i = 1:numel(outs)
        try
            pn = get_param(outs{i}, 'Port');
            nm = get_param(outs{i}, 'Name');
        catch %#ok<CTCH>
            pn = '?'; nm = '?';
        end
        w(sprintf('    Port%s: %s', mat2str(pn), nm));
    end

    % 2c. drive logic subsystem lines
    w(sprintf('  -- Subsystem (drive logic) top-level lines:'));
    dumpLines(fid, logicPath, logicPath);

    % 2d. key subsystem ports
    targets = { ...
        [mdl ':921'], 'appsrule'; ...
        [mdl ':2958'], 'angle sensor'; ...
        [mdl ':1816'], 'motor speed'; ...
        [mdl ':1977'], 'slip calc'; ...
        [mdl ':1011'], 'front wheel speed'; ...
        [mdl ':650'], 'brake-tail'; ...
        [mdl ':597'], 'brake-creep'};
    for t = 1:size(targets, 1)
        try
            sp = Simulink.ID.getFullName(targets{t, 1});
        catch %#ok<CTCH>
            continue;
        end
        w(sprintf(''));
        w(sprintf('  -- %s | %s', targets{t, 2}, sp));
        ins = find_system(sp, 'SearchDepth', 1, 'BlockType', 'Inport');
        outs2 = find_system(sp, 'SearchDepth', 1, 'BlockType', 'Outport');
        for i = 1:numel(ins)
            try
                pn = get_param(ins{i}, 'Port');
                nm = get_param(ins{i}, 'Name');
            catch %#ok<CTCH>
                pn = '?'; nm = '?';
            end
            w(sprintf('    IN  Port%s: %s', mat2str(pn), nm));
        end
        for i = 1:numel(outs2)
            try
                pn = get_param(outs2{i}, 'Port');
                nm = get_param(outs2{i}, 'Name');
            catch %#ok<CTCH>
                pn = '?'; nm = '?';
            end
            w(sprintf('    OUT Port%s: %s', mat2str(pn), nm));
        end
        dumpLines(fid, sp, sp);
    end

    % ================= 3. Named signal lines =================
    w(sprintf(''));
    w(sprintf('=== 3. NAMED SIGNAL LINES ==='));
    allLines = find_system(mdl, 'FindAll', 'on', 'Type', 'line');
    cnt = 0;
    for i = 1:numel(allLines)
        try
            nm = get_param(allLines(i), 'Name');
            if iscell(nm)
                if isempty(nm), continue; end
                nm = nm{1};
            end
            if isempty(nm), continue; end
            srcB = strCell(getfullname(get_param(allLines(i), 'SrcBlockHandle')));
            dstB = strCell(getfullname(get_param(allLines(i), 'DstBlockHandle')));
            cnt = cnt + 1;
            w(sprintf('  %s : %s -> %s', nm, srcB, dstB));
        catch %#ok<CTCH>
        end
    end
    w(sprintf('  total named lines: %d', cnt));

    w(sprintf(''));
    w(sprintf('LIST_DONE'));
    close_system(mdl, 0);
catch err
    w(sprintf(''));
    w(sprintf('LIST_ERROR'));
    w(getReport(err, 'extended'));
    try
        close_system(mdl, 0);
    catch %#ok<CTCH>
    end
end

end

function dumpLines(fid, sysPath, stripPath)
% DUMPLINES  One-level lines with names.
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
        srcB = strrep(strCell(getfullname(get_param(lh, 'SrcBlockHandle'))), [stripPath '/'], '');
        srcP = portStr(get_param(get_param(lh, 'SrcPortHandle'), 'PortNumber'));
    catch %#ok<CTCH>
        srcB = '?'; srcP = '?';
    end
    try
        dstB = strrep(strCell(getfullname(get_param(lh, 'DstBlockHandle'))), [stripPath '/'], '');
        dstP = portStr(get_param(get_param(lh, 'DstPortHandle'), 'PortNumber'));
    catch %#ok<CTCH>
        dstB = '?'; dstP = '?';
    end
    w(sprintf('    "%s" : %s:%s -> %s:%s', nm, srcB, srcP, dstB, dstP));
end
end

function s = strCell(v)
if iscell(v)
    if ~isempty(v)
        s = char(v{1});
    else
        s = '';
    end
elseif ischar(v)
    s = v;
else
    s = class(v);
end
end

function s = portStr(p)
if isnumeric(p)
    s = mat2str(p);
elseif ischar(p)
    s = p;
elseif iscell(p)
    s = portStr(p{1});
else
    s = class(p);
end
end
