# WCMI
Code for representing the dynamics of spatiotemporal data with non-redundant wavelets

Reference: 
“Representing the dynamics of high-dimensional data with non-redundant wavelets”
by Shanshan Jia,  Xingyi Li, Tiejun Huang, Jian K. Liu, Zhaofei Yu

## Basic environmental requirements:
linux system installed CMICOT and Matlab

To run the WCMI method, one needs to add two followng packages (both were cloned here):
1. WItoobox [https://www2.le.ac.uk/centres/csn/software/WI].
2. CMICOT [https://github.com/yandex/CMICOT]


## Steps:

1. Run WCMI_caller.m to save all the wavelet coefiicients in a txt file.

2. Run ' ./cmicot --pool simdata-ex1> simdata_ex1_feature_ranking --k' in terminal, to save the top k coefficients selected by CMI in a new txt

3. Run WCMI_decoding.m to get the decoding results.


## Datasets:

1. Simulated data: WItoolbox.zip contians the simulated data and the code for WI [https://www2.le.ac.uk/centres/csn/software/WI].

2. Experimental data: The experimental retinal neural data can be found at [https://doi.org/10.12751/g-node.kod28e].




