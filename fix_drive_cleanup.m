function fix_drive_cleanup()
% FIX_DRIVE_CLEANUP  Remove dead drive code and clean up block names.
% Does NOT touch power-on / framework logic.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'fix_cleanup_log.txt');

fid = fopen(outFile, 'w');
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));

    % ---------- 1. Delete dead wheel-speed / slip / monitor chain ----------
    deadSids = [1011, 1977, 2010, 2030, 2011, 2012, 3087, 3088, 3089, 3090, ...
                1961, 1971, 1828];
    for i = 1:numel(deadSids)
        sid = deadSids(i);
        try
            p = Simulink.ID.getFullName([mdl ':' num2str(sid)]);
        catch %#ok<CTCH>
            w(sprintf('skip missing sid %d', sid));
            continue;
        end
        try
            parent = get_param(p, 'Parent');
        catch %#ok<CTCH>
            w(sprintf('skip parentless %d', sid));
            continue;
        end
        lines = find_system(parent, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
        for j = 1:numel(lines)
            try
                srcB = strCell(getfullname(get_param(lines(j), 'SrcBlockHandle')));
                dstB = strCell(getfullname(get_param(lines(j), 'DstBlockHandle')));
            catch %#ok<CTCH>
                continue;
            end
            if strcmp(srcB, p) || strcmp(dstB, p)
                delete_line(lines(j));
            end
        end
        delete_block(p);
        w(sprintf('deleted %s', p));
    end

    % ---------- 2. Rename remaining blocks for clarity ----------
    renames = { ...
        546,  '驱动逻辑'; ...
        2933, '安全回路输出'; ...
        581,  '油门输出'; ...
        648,  '复位'; ...
        649,  '使能'; ...
        2932, '系统关键信号'; ...
        597,  '制动与待驶'; ...
        650,  '制动与尾灯'; ...
        3105, '油压1'; ...
        3102, '油压2'; ...
        921,  '油门规则'; ...
        1009, '油门原始值'; ...
        922,  '油门百分比'; ...
        923,  '刹车有效'; ...
        993,  '油门请求'; ...
        942,  '油门刹车冲突'; ...
        967,  '刹车判断'; ...
        980,  '油门死区判断'; ...
        929,  '动力允许判断'; ...
        2983, '油门数值处理'; ...
        3045, '百分比转化'; ...
        9,    '扭矩请求'; ...
        7,    '保留'; ...
        8,    '使能'; ...
        14,   '电机报文打包'; ...
        360,  'MCU_CAN发送'; ...
        1816, '电机测速'};
    for i = 1:size(renames, 1)
        sid = renames{i, 1};
        newName = renames{i, 2};
        try
            p = Simulink.ID.getFullName([mdl ':' num2str(sid)]);
            set_param(p, 'Name', newName);
            w(sprintf('renamed sid %d -> %s', sid, newName));
        catch err
            w(sprintf('rename failed sid %d: %s', sid, err.message));
        end
    end

    % ---------- 3. Save + verify ----------
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
    w(sprintf('CLEANUP_DONE'));
catch err
    w(sprintf('CLEANUP_ERROR'));
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
