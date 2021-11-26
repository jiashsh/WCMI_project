clear all
close all

% make handles global so all function will 'see' all parameters they need
global handles 

% below set the requiered parameters as you wish
handles.binsize = 1; % window length used to bin data
handles.nscales = 4; % number of scales for wavelet decomposition
handles.nsurr = 50; % number of surrogates for computing shuffling distribution
handles.percentile = 95; % percentile of surrogate distribution for significance
handles.maxwvcoefs =25; % maximum number of coefs to use
handles.minwvcoefs = 2; % mininum number of coefs to use
% below a mat file andd add the data to the global variable

pathn='.\data\';
name='simdata_cell_1'; % change to other data of interest
load([pathn,name,'.mat']);

handles.spiketimes = spiketimes; 
handles.class_id = class_id; 

% constructs binned matrix
WIfunc_binmatrix() 
disp('constructs binned matrix');
% computes wavelet decomposition
WIfunc_wavedec() 
disp('computes wavelet decomposition');

% save wavelets to file
fid=fopen([pathn,name],'w');
WVM=handles.matrices.wvmatrix;
CL=handles.class_id;
size(WVM,1);
for i=1: size(WVM,1)
	fprintf(fid,'%d\t',CL(i)-1);
	for j=1:size(WVM,2)-1
		fprintf(fid,'%f\t',WVM(i,j));
	end    
	fprintf(fid,'%f\n',WVM(i,end));
end
fclose(fid);
    
save([pathn,name,'_handles.mat'],'handles') 
