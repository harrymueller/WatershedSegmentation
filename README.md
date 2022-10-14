# Watershed Segmentation
## Harrison Mueller
 
## Supervisors
#### Harry Perkins: *Systems Biology and Genomics Laboratory*
 - Elena Denisenko
 - Alistair Forrest
 
#### UWA: *Computer Science Department*
 - Amitava Datta
 - Max Ward
 
The code is this repository was used as part of my honours project. 

## Functions
1. Crop images based on regions with low intensity, and save the cropped coordinates
2. Apply the watershed algorithm to the cropped image, producing a segmented image and a CSV file containing the IDs (plus 2 for the background)
3. Bin the segments into three files: 
   - `nuclei_coords.tsv` - average coordinates of each nuclei
   - `nuclei_spots.tsv` - the mapping of each spot to the nuclei id
   - `nuclei.gem` - contains the geneID, nucleiID and MIDCount