#include "binning.hpp"

void Binning::bin(Opts opts)
{
    std::cout << "Reading markers csv..." << std::endl;
    Mat im = Binning::read_markers(opts.input_file);

    // spots to nuclei and average spot coords
    //std::cout << "Binning spots..." << std::endl;
    //NucleiSpots::nuclei_spots(im, opts.output_dir);
    
    std::cout << "Binning genes from GEM file..." << std::endl;
    GEM::gem(im, opts);

    std::cout << "Binning completed." << std::endl;
}

/*
    Given an image csv containing segments, creates an image object
*/
Mat Binning::read_markers(std::string filename)
{
    // template variables
    std::string l, val;
    std::vector<std::vector<int>> data;
    std::vector<int> row;
    int i, j;

    // open file and check that it is valid
    std::fstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file '" << filename << "'\n";
        exit(EXIT_FAILURE);
    }

    // read line by line
    while (std::getline(file, l)) {
        row.clear();

        std::stringstream temp(l);
        while (getline(temp, val, ',')) {
            row.push_back(atoi(val.c_str()));
        }
        data.push_back(row);
    }

    // Now add all the data into a Mat element
    Mat im = Mat::zeros((int) data.size(), (int) data[0].size(), CV_32S);
    // Loop over vectors and add the data
    for ( i = 0; i < (int) data.size(); i++ ){
        for ( j= 0; j< (int) data[0].size(); j++ ){
            im.at<int>(i,j) = data[i][j];
        }
    }

    return im;
}


/*
    Finds the largest bin id, searches from bottom right to top right, rows first
    go through last 16 rows (from first id) looking for max
*/
int Binning::find_max_bin_id(Mat im) {
    int i, j, val;
    int max_so_far = -1;
    int first_row = 0;

    for ( i = im.rows - 1; i > first_row - 17; i-- ) { // y 
        for ( j = im.cols - 1; j >= 0; j-- ) { // x
            val = im.at<int>(i,j);
            if (first_row == 0 && max_so_far > 1) first_row=i;
            if (val > max_so_far)
                max_so_far = val;
        }
    }

    return max_so_far - 1;
}