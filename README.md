# WCMI
Code for representing the dynamics of spatiotemporal data with non-redundant wavelets

Accompanying the manuscript
“Representing the dynamics of high-dimensional data with non-redundant wavelets”
by Shanshan Jia,  Xingyi Li, Tiejun Huang, Jian K. Liu, Zhaofei Yu


Contact: Jian K. Liu, Zhaofei Yu
https://github.com/jiashsh/WCMI_project

## Quick start

#Basic environmental requirements
Matlab
linux system has been installed CMICOT


#First step，
Run WCMI_caller.m to save all the wavelet coefiicients in a txt file.

#Second step，
Run 
' ./cmicot --pool simdata-ex1> simdata_ex1_feature_ranking_6s --k' 
in terminal, to save the top-k coefficients and their scores selected by CMI in a new txt

#Third step，
Run WCMI_decoding.m to get the decoding results.
 
