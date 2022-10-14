#ifndef NUCLEI_SPOTS_
#define NUCLEI_SPOTS_


// cpp libs
#include <cmath>
#include <iostream>
#include <fstream>

// CV lib
#include <opencv2/opencv.hpp>
using namespace cv;

#include "binning.hpp"

namespace NucleiSpots
{
    void nuclei_spots(Mat, std::string);
    void nuclei_coords(int, std::vector<std::vector<uint>>, std::string);
    void stats(int, int, int, std::vector<std::vector<uint>>, std::string);

    int find_max_bin_id(Mat);
}

#endif
