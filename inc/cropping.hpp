#ifndef CROPPING_
#define CROPPING_

// STD libs
#include <stdio.h>
#include <iostream>
#include <fstream>

// image class and opts DS
#include "image.hpp"
#include "opts.hpp"

// cv
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
using namespace cv;


namespace Cropping 
{
    void crop(Opts);
    void compare_pos(int, int, int*);
    void add_buffer(int*, int);
    void save_dim(int *, std::string);
}

#endif