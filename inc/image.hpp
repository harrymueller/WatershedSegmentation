#ifndef IMAGE_
#define IMAGE_

#include <stdio.h>
#include <iostream>
#include <fstream>

// cv
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
using namespace cv;

#define NOT_EXTRA_VERBOSE

/*
    Image class:
        stores a cv::Mat obj, and provides many methods for the given matrix
*/
class Image {
    public:
        // attributes

        // constructor
        Image(std::string filename);
        Image(Mat im);

        // destructor
        ~Image();

        // accessor methods
        Mat get_im();
        void set_im(Mat);
        
        // methods
        int display();
        int save(std::string);
        Image duplicate();

        // width and height
        int width();
        int height();

        int get_value(int, int);

        void applyMask(Image);
        void applyMask(Mat);

        void subtract(Image);

        void convertColour(int);
        void convertType(int);

        void apply(Image, std::function<void(Mat, Mat, int, int)>);
        void apply(std::function<void(Mat, int, int)>);

        void save_to_csv(std::string);

        void crop(int, int, int, int);
    private:
        // attributes
        Mat im; // image matrix
};

#endif