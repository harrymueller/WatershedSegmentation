#ifndef WATERSHED_
#define WATERSHED_

// cv
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

// image class
#include "image.hpp"

// OPTS struct
#include "opts.hpp"

#include "thresholds.hpp"
#include "fg_bg.hpp"

namespace Watershed {
    Image get_markers(Image, Image);
    Image apply_watershed(Image, Image);
    Image outline(Image, Image);
    void watershed(Opts);
    void threshold(Opts);
}
#endif