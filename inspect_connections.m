function inspect_connections()
% INSPECT_CONNECTIONS  Dump line connectivity inside key drive subsystems.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'drive_connections.txt');

fid = fopen(outFile, 'w');
if fid < 0
    error('inspect_connections:open', 'Cannot open report file: %s', outFile);
end
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));
    drivePath = Simulink.ID.getFullName([mdl ':2']);

    % Subsystems to inspect, by SID (must be inside drive)
    targets = { ...
        [mdl ':2'],                            'DRIVE top'; ...
        [mdl ':546'],                          'Subsystem (drive logic)'; ...
        [mdl ':921'],                          'appsrule'; ...
        [mdl ':650'],                          'brake-tail'; ...
        [mdl ':1977'],                         'slip calc'; ...
        [mdl ':1816'],                         'motor speed'; ...
        [mdl ':2958'],                         'angle sensor'; ...
        [mdl ':2963'],                         'angle processing' ...
    };

    for t = 1:size(targets, 1)
        sid = targets{t, 1};
        label = targets{t, 2};
        try
            sysPath = Simulink.ID.getFullName(sid);
        catch err
            w(sprintf('=== %s (%s) === <skip: %s>', label, sid, err.message));
            continue;
        end
        w(sprintf(''));
        w(sprintf('=== %s | %s ===', label, sysPath));
        dumpSys(fid, sysPath);
    end

    w(sprintf(''));
    w(sprintf('CONNECTIONS_DONE'));
    close_system(mdl, 0);
catch err
    w(sprintf(''));
    w(sprintf('CONNECTIONS_ERROR'));
    w(getReport(err, 'extended'));
    try
        close_system(mdl, 0);
    catch %#ok<CTCH>
    end
end

end

function dumpSys(fid, sysPath)
% DUMP_SYS  Dump one level of blocks, ports and lines for sysPath.
w = @(s) fprintf(fid, '%s\n', s);

% Blocks at this level
blks = find_system(sysPath, 'SearchDepth', 1, 'Type', 'block');
blks(cellfun(@(b) strcmp(b, sysPath), blks)) = [];
w(sprintf('-- blocks (%d):', numel(blks)));
for i = 1:numel(blks)
    b = blks{i};
    try
        bt = get_param(b, 'BlockType');
    catch %#ok<CTCH>
        bt = '?';
    end
    try
        sid = Simulink.ID.getSID(b);
    catch %#ok<CTCH>
        sid = '?';
    end
    try
        nports = mat2str(get_param(b, 'Ports'));
    catch %#ok<CTCH>
        nports = '?';
    end
    short = strrep(b, [sysPath '/'], '');
    w(sprintf('    [%s] %s | %s | Ports=%s', sid, short, bt, nports));
end

% Lines at this level
lines = find_system(sysPath, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
w(sprintf('-- lines (%d):', numel(lines)));
for i = 1:numel(lines)
    lh = lines(i);
    try
        lname = get_param(lh, 'Name');
        if isempty(lname)
            lname = '(unnamed)';
        end
    catch %#ok<CTCH>
        lname = '(unnamed)';
    end
    try
        srcB = getfullname(get_param(lh, 'SrcBlockHandle'));
        srcP = get_param(get_param(lh, 'SrcPortHandle'), 'PortNumber');
    catch %#ok<CTCH>
        srcB = '?';
        srcP = '?';
    end
    try
        dstB = getfullname(get_param(lh, 'DstBlockHandle'));
        dstP = get_param(get_param(lh, 'DstPortHandle'), 'PortNumber');
    catch %#ok<CTCH>
        dstB = '?';
        dstP = '?';
    end
    srcShort = strrep(srcB, [sysPath '/'], '');
    dstShort = strrep(dstB, [sysPath '/'], '');
    lname = strCell(lname);
    srcShort = strCell(srcShort);
    dstShort = strCell(dstShort);
    srcPS = portStr(srcP);
    dstPS = portStr(dstP);
    w(sprintf('    "%s": %s :%s -> %s :%s', lname, srcShort, srcPS, dstShort, dstPS));
end
end

function s = strCell(v)
% STRCELL  Convert a char/cell value to a plain char.
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
% PORTSTR  Render a port number (numeric or char) as a string.
if isnumeric(p)
    s = mat2str(p);
elseif ischar(p)
    s = p;
else
    s = class(p);
end
end
