function inspect_drive()
% INSPECT_DRIVE  Dump detailed structure of text28 drive subsystem (SID 2).

mdl = 'text28';
srcDir = fileparts(mfilename('fullpath'));
outFile = fullfile(srcDir, 'drive_structure.txt');

fid = fopen(outFile, 'w');
if fid < 0
    error('inspect_drive:open', 'Cannot open report file: %s', outFile);
end
w = @(s) fprintf(fid, '%s\n', s);
cleanup = onCleanup(@() fclose(fid));

try
    load_system(fullfile(srcDir, [mdl '.slx']));
    drivePath = Simulink.ID.getFullName([mdl ':2']);
    w(sprintf('DRIVE_PATH=%s', drivePath));
    w(sprintf(''));

    % ---- Recursively dump all blocks under the drive subsystem ----
    blocks = find_system(drivePath, 'LookUnderMasks', 'all', 'FollowLinks', 'on', 'Type', 'block');
    w(sprintf('=== ALL BLOCKS UNDER DRIVE (%d) ===', numel(blocks)));
    for i = 1:numel(blocks)
        b = blocks{i};
        try
            sid = Simulink.ID.getSID(b);
        catch %#ok<CTCH>
            sid = '?';
        end
        try
            bt = get_param(b, 'BlockType');
        catch %#ok<CTCH>
            bt = 'Unknown';
        end
        params = paramSummary(b, bt);
        w(sprintf('[%s] %s | %s%s', sid, b, bt, params));
    end

    w(sprintf(''));
    w(sprintf('INSPECT_DONE'));
    close_system(mdl, 0);
catch err
    w(sprintf(''));
    w(sprintf('INSPECT_ERROR'));
    w(getReport(err, 'extended'));
    try
        close_system(mdl, 0);
    catch %#ok<CTCH>
    end
end

end

function s = paramSummary(b, bt)
% PARAMSUMMARY  Return a compact string of interesting parameters.
s = '';
names = {};
switch bt
    case 'Constant'
        names = {'Value', 'OutDataTypeStr'};
    case 'Gain'
        names = {'Gain', 'OutDataTypeStr'};
    case 'Sum'
        names = {'Inputs', 'Signs', 'OutDataTypeStr'};
    case 'Product'
        names = {'Inputs', 'Multiplication', 'OutDataTypeStr'};
    case 'Switch'
        names = {'Criteria', 'Threshold', 'AllowDifferentDataTypes'};
    case 'If'
        names = {'IfExpression', 'ElseIfExpressions', 'ShowElse'};
    case 'RelationalOperator'
        names = {'Operator'};
    case 'UnitDelay'
        names = {'SampleTime', 'InitialCondition'};
    case 'S-Function'
        names = {'FunctionName', 'Parameters'};
    case 'Inport'
        names = {'Port', 'OutDataTypeStr', 'SampleTime'};
    case 'Outport'
        names = {'Port', 'OutDataTypeStr', 'SampleTime', 'InitialOutput'};
    case 'DataTypeConversion'
        names = {'OutDataTypeStr', 'ConvertRealWorld'};
    case 'Saturate'
        names = {'UpperLimit', 'LowerLimit'};
    case 'ArithShift'
        names = {'ShiftNumber', 'Direction', 'DataTypeMode'};
    case 'Rounding'
        names = {'RndMeth'};
    case 'Logic'
        names = {'Operator', 'Inputs'};
    case 'Mux'
        names = {'Inputs'};
    case 'Demux'
        names = {'Outputs'};
    case 'Merge'
        names = {'Inputs', 'AllowUnequalInputPortWidths'};
    case 'Terminator'
        names = {};
    case 'ActionPort'
        names = {'StateWhenAtomicSubsystem'};
    case 'TriggerPort'
        names = {'TriggerType'};
    case 'SubSystem'
        names = {};
    otherwise
        names = {};
end

out = {};
for i = 1:numel(names)
    try
        v = get_param(b, names{i});
        if ischar(v)
            v = v;
        elseif isnumeric(v)
            v = mat2str(v);
        else
            v = class(v);
        end
        out{end+1} = sprintf('%s=%s', names{i}, v); %#ok<AGROW>
    catch %#ok<CTCH>
    end
end
if ~isempty(out)
    s = sprintf(' | %s', strjoin(out, ', '));
end
end
