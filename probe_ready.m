function probe_ready()
% PROBE_READY  Dump ready-to-drive logic and CAN-ok related blocks.

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'probe_ready.txt');

fid = fopen(outFile, 'w');
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));

    % ---- Ready subsystem ----
    readyPath = Simulink.ID.getFullName([mdl ':597']);
    w(sprintf('READY=%s', readyPath));
    blks = find_system(readyPath, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'Type', 'block');
    for i = 1:numel(blks)
        b = blks{i};
        try
            bt = get_param(b, 'BlockType');
            sid = Simulink.ID.getSID(b);
        catch %#ok<CTCH>
            bt = '?'; sid = '?';
        end
        extra = '';
        switch bt
            case {'Constant','Gain','Saturate','Sum','Product','UnitDelay','Switch','If'}
                names = {'Value','Gain','UpperLimit','LowerLimit','Inputs','Signs','InitialCondition','Criteria','Threshold','IfExpression','ElseIfExpressions','FunctionName'};
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
                        extra = [extra names{j} '=' vs '; ']; %#ok<AGROW>
                    catch %#ok<CTCH>
                    end
                end
            case 'S-Function'
                try
                    extra = ['FunctionName=' get_param(b, 'FunctionName')];
                catch %#ok<CTCH>
                end
        end
        short = strrep(b, [readyPath '/'], '');
        w(sprintf('[%s] %s | %s | %s', sid, short, bt, extra));
    end

    % ---- CAN-ok / livecounter blocks under motor speed ----
    motorPath = Simulink.ID.getFullName([mdl ':1816']);
    w(sprintf(''));
    w(sprintf('MOTOR=%s', motorPath));
    blks2 = find_system(motorPath, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'Type', 'block');
    for i = 1:numel(blks2)
        b = blks2{i};
        if isempty(strfind(b, 'Livecounter')) && isempty(strfind(b, 'CAN'))
            continue;
        end
        try
            bt = get_param(b, 'BlockType');
            sid = Simulink.ID.getSID(b);
        catch %#ok<CTCH>
            bt = '?'; sid = '?';
        end
        extra = '';
        try
            if strcmp(bt, 'S-Function')
                extra = ['FunctionName=' get_param(b, 'FunctionName')];
            elseif strcmp(bt, 'RelationalOperator')
                extra = ['Operator=' get_param(b, 'Operator')];
            elseif strcmp(bt, 'Constant')
                extra = ['Value=' mat2str(get_param(b, 'Value'))];
            elseif strcmp(bt, 'Saturate')
                extra = ['Upper=' mat2str(get_param(b, 'UpperLimit')) ' Lower=' mat2str(get_param(b, 'LowerLimit'))];
            elseif strcmp(bt, 'Switch')
                extra = ['Criteria=' get_param(b, 'Criteria')];
            elseif strcmp(bt, 'Sum')
                extra = ['Inputs=' get_param(b, 'Inputs')];
            end
        catch %#ok<CTCH>
        end
        short = strrep(b, [motorPath '/'], '');
        w(sprintf('[%s] %s | %s | %s', sid, short, bt, extra));
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
