clear all
close all %,clc,

% make handles global so all function will 'see' all parameters they need
global handles 

pathn='.\data\';
name='simdata_cell_1';
load([pathn,name,'.mat']);
load([pathn,name,'_handles.mat']) 

% features and their scores selected by CMI
features=textread([pathn,name,'_feature_ranking_6s']);
handles.matrices.selected_wcmicoefs=features(:,2);

% a LDA decoder
WCMIfunc_decode_leaveoneout();

handles.decode
    
