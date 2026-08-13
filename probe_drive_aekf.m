function probe_drive_aekf()
% PROBE_DRIVE_AEKF  Verify Drive_AEKF wiring after integration.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'probe_aekf.txt');

fid = fopen(outFile, 'w');
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));
    logicPath = Simulink.ID.getFullName([mdl ':546']);
    tcs = [logicPath '/Drive_AEKF'];
    w(sprintf('AEKF=%s', tcs));

    % Blocks inside Drive_TCS (one level)
    blks = find_system(tcs, 'SearchDepth', 1, 'Type', 'block');
    blks(cellfun(@(b) strcmp(b, tcs), blks)) = [];
    w(sprintf('-- blocks (%d):', numel(blks)));
    for i = 1:numel(blks)
        try
            bt = get_param(blks{i}, 'BlockType');
        catch %#ok<CTCH>
            bt = '?';
        end
        short = strrep(blks{i}, [tcs '/'], '');
        w(sprintf('    %s | %s', short, bt));
    end

    % Lines inside Drive_TCS
    lines = find_system(tcs, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
    w(sprintf('-- lines (%d):', numel(lines)));
    for i = 1:numel(lines)
        lh = lines(i);
        try
            srcB = strCell(getfullname(get_param(lh, 'SrcBlockHandle')));
            srcB = strrep(srcB, [tcs '/'], '');
            srcP = get_param(get_param(lh, 'SrcPortHandle'), 'PortNumber');
        catch %#ok<CTCH>
            srcB = '?'; srcP = '?';
        end
        try
            dstB = strCell(getfullname(get_param(lh, 'DstBlockHandle')));
            dstB = strrep(dstB, [tcs '/'], '');
            dstP = get_param(get_param(lh, 'DstPortHandle'), 'PortNumber');
        catch %#ok<CTCH>
            dstB = '?'; dstP = '?';
        end
        w(sprintf('    %s:%s -> %s:%s', srcB, any2str(srcP), dstB, any2str(dstP)));
    end

    % Subsystem top-level lines involving Drive_TCS
    w(sprintf('-- Subsystem top lines:')); 
    lines2 = find_system(logicPath, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
    for i = 1:numel(lines2)
        lh = lines2(i);
        try
            srcB = strCell(getfullname(get_param(lh, 'SrcBlockHandle')));
            srcB = strrep(srcB, [logicPath '/'], '');
            dstB = strCell(getfullname(get_param(lh, 'DstBlockHandle')));
            dstB = strrep(dstB, [logicPath '/'], '');
        catch %#ok<CTCH>
            srcB = '?'; dstB = '?';
        end
    if ~isempty(strfind(srcB, 'Drive_AEKF')) || ~isempty(strfind(dstB, 'Drive_AEKF'))
            w(sprintf('    %s -> %s', srcB, dstB));
        end
    end

    w(sprintf('PROBE_DONE'));
    close_system(mdl, 0);
catch err
    w(sprintf('PROBE_ERROR'));
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

function s = any2str(v)
if isnumeric(v)
    s = mat2str(v);
elseif ischar(v)
    s = v;
elseif iscell(v)
    s = any2str(v{1});
else
    s = class(v);
end
end
