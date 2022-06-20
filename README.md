# ssDNA_nuclei_segmentation
This program has three functions:
1. Crop images based on regions with low intensity, and save the cropped coordinates
2. Apply the watershed algorithm to the cropped image, producing a segmented image and a CSV file containing the IDs (plus 2 for the background)
3. Bin the segments into three files: 
   - `nuclei_coords.tsv` - average coordinates of each nuclei
   - `nuclei_spots.tsv` - the mapping of each spot to the nuclei id
   - `nuclei.gem` - contains the geneID, nucleiID and MIDCount
