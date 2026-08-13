function probe_channels()
% PROBE_CHANNELS  Dump actual channel / CAN parameters of hardware S-Functions
% in the ORIGINAL text28 model.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'channels.txt');

fid = fopen(outFile, 'w');
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));
    blocks = find_system(mdl, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'BlockType', 'S-Function');
    for i = 1:numel(blocks)
        b = blocks{i};
        try
            fn = get_param(b, 'FunctionName');
        catch err
            fn = '?';
        end
        if isempty(strfind(fn, 'ec55xx_')) && isempty(strfind(fn, 'sfix_'))
            continue;
        end
        try
            maskNames = get_param(b, 'MaskNames');
        catch %#ok<CTCH>
            maskNames = {};
        end
        vals = '';
        for j = 1:numel(maskNames)
            try
                v = get_param(b, maskNames{j});
                if ischar(v)
                    vs = v;
                elseif isnumeric(v)
                    vs = mat2str(v);
                else
                    vs = class(v);
                end
                vals = [vals maskNames{j} '=' vs '; ']; %#ok<AGROW>
            catch %#ok<CTCH>
            end
        end
        if isempty(vals)
            try
                dlg = get_param(b, 'DialogParameters');
                names = fieldnames(dlg);
                for j = 1:numel(names)
                    try
                        v = get_param(b, names{j});
                        if ischar(v)
                            vs = v;
                        elseif isnumeric(v)
                            vs = mat2str(v);
                        else
                            vs = class(v);
                        end
                        vals = [vals names{j} '=' vs '; ']; %#ok<AGROW>
                    catch %#ok<CTCH>
                    end
                end
            catch %#ok<CTCH>
            end
        end
        w(sprintf('%s | %s | %s', b, fn, vals));
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
