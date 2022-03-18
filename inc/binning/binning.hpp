#ifndef BINNING_
#define BINNING_


// cpp libs
#include <iostream>
#include <fstream>

// CV lib
#include <opencv2/opencv.hpp>
using namespace cv;

// headers
#include "opts.hpp"
#include "nuclei_spots.hpp"
#include "gem.hpp"

namespace Binning {
    void bin(Opts);

    Mat read_markers(std::string);
    int find_max_bin_id(Mat);
}

#endif