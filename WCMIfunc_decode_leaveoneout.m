function WCMIfunc_decode_leaveoneout()

global handles


spkcount = sum(handles.matrices.actmatrix,2);
class_labels = unique(handles.class_id);
nclasses = length(class_labels);
ntrials = length(spkcount);

dec_output = nan(ntrials,1);
    
    for trial_i = 1:ntrials
        handles.decode.testingtrial = trial_i;
        handles.decode.trainingtrials = setdiff(1:ntrials,trial_i);

        sample = ...
            handles.matrices.wvmatrix(trial_i,...
            handles.matrices.selected_wcmicoefs+1);
        training = ...
            handles.matrices.wvmatrix(handles.decode.trainingtrials,...
            handles.matrices.selected_wcmicoefs+1);
        training = training+rand(size(training))/999999999; 
        class_id_training = ...
            handles.class_id(handles.decode.trainingtrials);
        dec_output(trial_i) = ...
            classify(sample,training,class_id_training,'diagLinear');
    end
    handles.decode.WCMIconfusionmatrix = ...
        confusionmat(handles.class_id,dec_output)';
    handles.decode.WCMIperf = ...
        sum(handles.class_id(:)==dec_output(:))/length(dec_output);

end

