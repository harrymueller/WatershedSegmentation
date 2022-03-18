#ifndef GEM_
#define GEM_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

// CV lib
#include <opencv2/opencv.hpp>
using namespace cv;

#include "binning.hpp"
#include "opts.hpp"

class GEMLine
{
    public:
        std::string gene;
        uint x, y, count;
        GEMLine(std::string);
        GEMLine();
};

namespace GEM
{
    void gem(Mat, Opts);

    std::vector<GEMLine> read_gem(std::string, int *);
    bool comp(GEMLine, GEMLine);

    void add_header_to_output(std::string);
    void save_genes(std::string, std::string, int, std::vector<uint>);
}


#endif