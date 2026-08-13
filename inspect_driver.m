function inspect_driver()
% INSPECT_DRIVER  Run the full-model audit under R2014a, write a done flag,
% and exit cleanly.
try
    inspect_full_model();
catch err
    fid = fopen(fullfile(pwd, 'audit_error.txt'), 'w');
    if fid > 0
        fprintf(fid, '%s\n', getReport(err, 'extended'));
        fclose(fid);
    end
end
fid = fopen(fullfile(pwd, 'audit_done.txt'), 'w');
if fid > 0
    fprintf(fid, 'done\n');
    fclose(fid);
end
exit;
end
