#ifndef PLOTTING_
#define PLOTTING_

// cpp libs
#include <iostream>
#include <fstream>
// cv
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
using namespace cv;

#include "opts.hpp"
#include "binning.hpp"
#include "image.hpp"

class IdVal 
{
    public: 
        uint id;
        int val;
        IdVal(int, int);
        IdVal();
};

namespace Plotting 
{
    void plot_wrapper(Opts);
    std::vector<int> read_plot_tsv(std::string, int, plot_types);
    IdVal string_to_int(std::string, plot_types);
    //void plot_rgb(*std::vector<uint>);
}


#endif

