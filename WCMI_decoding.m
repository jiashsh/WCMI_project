clear all
close all

% make handles global so all function will 'see' all parameters they need
global handles 

pathn='.\data\';
%name='simdata_cell_1'; 
name='simdata_cell_1'; 
load([pathn,name,'_handles.mat']) 

% features and their scores selected by CMI
features=textread([pathn,name,'_feature_ranking_6s']);
handles.matrices.selected_wcmicoefs=features(:,2);

% Decoding with LDA decoder
WCMIfunc_decode_leaveoneout();

handles.decode
    
figure
Ntrial=sum(handles.class_id==1);
Nclass=handles.class_id(end);
imagesc(handles.decode.WCMIconfusionmatrix/Ntrial);
colorbar;
xticks([1:1:Nclass]);
yticks([1:1:Nclass]);
xlabel('Actual Stimulus');
ylabel('Predicted Stimulus');
title('Confusion Matrix');
