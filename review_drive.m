function review_drive()
% REVIEW_DRIVE  Full connection/structure review of drive-related subsystems.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, '驱动审查_详细.txt');

fid = fopen(outFile, 'w');
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));

    targets = { ...
        [mdl ':2'],    '驱动系统 top'; ...
        [mdl ':546'],  'Subsystem (drive logic)'; ...
        [mdl ':921'],  'appsrule'; ...
        [mdl ':2963'], 'angle processing'; ...
        [mdl ':2970'], 'unreliable judge'; ...
        [mdl ':2983'], 'pedal value'; ...
        [mdl ':3045'], 'percent conversion'; ...
        [mdl ':3069'], 'sensor ok'; ...
        [mdl ':650'],  'brake-tail'; ...
        [mdl ':597'],  'brake-ready'; ...
        [mdl ':669'],  'ready activation'; ...
        [mdl ':1816'], 'motor speed'; ...
        [mdl ':1829'], 'receive messages'; ...
        [mdl ':1842'], 'resive1'; ...
        [mdl ':6'],    'ECU'; ...
        [mdl ':14'],   'ECU/Motor'; ...
        [mdl ':1011'], 'front wheel speed'; ...
        [mdl ':1977'], 'slip calc'; ...
        [mdl ':2933'], 'safety out subsystem'};

    for t = 1:size(targets, 1)
        try
            sp = Simulink.ID.getFullName(targets{t, 1});
        catch %#ok<CTCH>
            w(sprintf('=== %s | %s === <skip>', targets{t, 2}, targets{t, 1}));
            continue;
        end
        w(sprintf(''));
        w(sprintf('=== %s | %s ===', targets{t, 2}, sp));
        % direct children
        blks = find_system(sp, 'SearchDepth', 1, 'Type', 'block');
        blks(cellfun(@(b) strcmp(b, sp), blks)) = [];
        for i = 1:numel(blks)
            b = blks{i};
            try
                bt = get_param(b, 'BlockType');
                sid = Simulink.ID.getSID(b);
            catch %#ok<CTCH>
                bt = '?'; sid = '?';
            end
            try
                ports = mat2str(get_param(b, 'Ports'));
            catch %#ok<CTCH>
                ports = '?';
            end
            short = strrep(b, [sp '/'], '');
            w(sprintf('  BLK [%s] %s | %s | Ports=%s', sid, short, bt, ports));
        end
        % lines at this level
        lines = find_system(sp, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
        for i = 1:numel(lines)
            lh = lines(i);
            try
                nm = get_param(lh, 'Name');
                nm = strCell(nm);
                if isempty(nm), nm = '(unnamed)'; end
            catch %#ok<CTCH>
                nm = '(unnamed)';
            end
            try
                srcB = strrep(strCell(getfullname(get_param(lh, 'SrcBlockHandle'))), [sp '/'], '');
                srcP = portStr(get_param(get_param(lh, 'SrcPortHandle'), 'PortNumber'));
            catch %#ok<CTCH>
                srcB = '?'; srcP = '?';
            end
            try
                dstB = strrep(strCell(getfullname(get_param(lh, 'DstBlockHandle'))), [sp '/'], '');
                dstP = portStr(get_param(get_param(lh, 'DstPortHandle'), 'PortNumber'));
            catch %#ok<CTCH>
                dstB = '?'; dstP = '?';
            end
            w(sprintf('  LINE "%s": %s:%s -> %s:%s', nm, srcB, srcP, dstB, dstP));
        end
    end

    % Drive_AEKF by name
    logicPath = Simulink.ID.getFullName([mdl ':546']);
    aekf = find_system(logicPath, 'SearchDepth', 1, 'Name', 'Drive_AEKF');
    if ~isempty(aekf)
        w(sprintf(''));
        w(sprintf('=== Drive_AEKF | %s ===', aekf{1}));
        blks = find_system(aekf{1}, 'SearchDepth', 1, 'Type', 'block');
        blks(cellfun(@(b) strcmp(b, aekf{1}), blks)) = [];
        for i = 1:numel(blks)
            try
                bt = get_param(blks{i}, 'BlockType');
            catch %#ok<CTCH>
                bt = '?';
            end
            w(sprintf('  BLK %s | %s', strrep(blks{i}, [aekf{1} '/'], ''), bt));
        end
        lines = find_system(aekf{1}, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
        for i = 1:numel(lines)
            lh = lines(i);
            try
                srcB = strrep(strCell(getfullname(get_param(lh, 'SrcBlockHandle'))), [aekf{1} '/'], '');
                dstB = strrep(strCell(getfullname(get_param(lh, 'DstBlockHandle'))), [aekf{1} '/'], '');
            catch %#ok<CTCH>
                srcB = '?'; dstB = '?';
            end
            w(sprintf('  LINE %s -> %s', srcB, dstB));
        end
    end

    w(sprintf(''));
    w(sprintf('REVIEW_DONE'));
    close_system(mdl, 0);
catch err
    w(sprintf('REVIEW_ERROR'));
    w(getReport(err, 'extended'));
    try
        close_system(mdl, 0);
    catch %#ok<CTCH>
    end
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
