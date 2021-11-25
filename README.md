# WCMI - Wavelet Conditional Mutual Information
Code for representing the dynamics of spatiotemporal data with non-redundant wavelets

Reference: 
“Representing the dynamics of high-dimensional data with non-redundant wavelets”
by Shanshan Jia,  Xingyi Li, Tiejun Huang, Jian K. Liu, Zhaofei Yu

## Basic environmental requirements:
linux system installed CMICOT and Matlab

To run the WCMI method, one needs to add two following packages (both were cloned here):
1. WItoobox [https://www2.le.ac.uk/centres/csn/software/WI]: here one can implment the wavelet decompsition and compute mutual formation of each feature.
2. CMICOT [https://github.com/yandex/CMICOT]: we have updated the code, so that one can output the ranking ID of each feature, together with the conditional mutual information value of each feature.


## Steps:

1. Run WCMI_caller.m to save all the wavelet coefiicients in a txt file.

2. Run ' ./cmicot --pool simdata_cell_1> simdata_cell_1_feature_ranking_6s --select-count k' in terminal, to save the top k coefficients selected by CMI in a new txt.

3. Run WCMI_decoding.m to get the decoding results.


## Datasets:

1. Simulated data: The data folder contians the simulated data takend from WItoobox.

2. Experimental data - 'Retinal ganglion cell responses to natural images' can be found at [https://doi.org/10.12751/g-node.kod28e].

3. Experimental data - 'Human ECoG speaking consonant-vowel syllables' can be found at [https://doi.org/10.6084/m9.figshare.c.4617263.v4].




