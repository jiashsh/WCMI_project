clear all;
close all;

% First, download responses2naturalimages.h5 at https://doi.gin.g-node.org/10.12751/g-node.kod28e/

% make handles global so all function will 'see' all parameters they need
global handles 

% below set the requiered parameters as you wish
handles.binsize = 1; % window length used to bin data
handles.nscales = 4; % number of scales for wavelet decomposition

pathn='.\data\';
name='naturalimages';
% Load spike rasters
spikedata = h5read('responses2naturalimages.h5','/spikes');

% IDs for sample cells and images
Ncell=20;
Nimage=10;
CellID = 1:1:20;
ImageID = 1:1:10;

% Get spike rasters for sample cells and sample images
data = squeeze(spikedata(:,:,:,CellID));
Raster = squeeze(data(:,:,ImageID,:));
% Get all the trials for this cell and image
NTrial = size(Raster,2);

% compute wavelet decomposition of population
WVM=[];
actmatrix=[];
for i=1:Ncell
    temp=Raster(:,:,:,i);
    spike=[];
    for j=1:Nimage
        spike=[spike;temp(:,:,j)'];
    end
    actmatrix=[actmatrix,spike];
    handles.matrices.actmatrix=spike;
    WIfunc_wavedec() % computes wavelet decomposition
    WVM=[WVM,handles.matrices.wvmatrix];
end
class_id=[];
for im=1:Nimage
	class_id((im-1)*NTrial+[1:NTrial])=im*ones(1,NTrial);
end 
handles.class_id = class_id; 
handles.matrices.actmatrix=actmatrix;
handles.matrices.wvmatrix=WVM;

% save wavelets to file
fid=fopen([pathn,name],'w');
CL=handles.class_id;
size(WVM,1);
for iw=1: size(WVM,1)
	fprintf(fid,'%d\t',CL(iw)-1);
	for jw=1:size(WVM,2)-1
     	fprintf(fid,'%f\t',WVM(iw,jw));
    end    
	fprintf(fid,'%f\n',WVM(iw,end));
end
fclose(fid);

save([pathn,name,'_handles.mat'],'handles') 
