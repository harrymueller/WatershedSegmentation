#include "image.hpp"


/*##############################
    CONSTRUCTORS
##############################*/
void isValid(Mat);

Image::Image(Mat im)
{
    this->im = im;
    isValid(this->im);
}

Image::Image(std::string filename)
{
    this->im = imread( filename, IMREAD_GRAYSCALE );
    isValid(this->im);
}

void isValid(Mat im) {
    if (!im.data) {
        std::cout << "Input is not a valid image file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

/*##############################
    DESTRUCTOR
##############################*/
Image::~Image()
{
    ~this->im;
}

/*##############################
    ACCESSOR METHODS
##############################*/
Mat Image::get_im()
{
    return this->im;
}

void Image::set_im(Mat im)
{
    this->im = im;
}

/*##############################
    METHODS
##############################*/
// displays this image in a window
int Image::display() 
{
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", this->im);
    waitKey(0);
    return 0;
}

// saves this image to the filename given
int Image::save(std::string filename) 
{
    bool x = imwrite(filename, this->im);
    #ifndef NOT_EXTRA_VERBOSE
    std::cout << "Saved image to " << filename << std::endl;
    #endif
    return x ? 0 : 1;
}   

// returns a copy of this obj 
Image Image::duplicate() 
{
    return Image(this->im.clone());
}

// im sizes
int Image::width()
{
    return this->im.size().width;
}
int Image::height()
{
    return this->im.size().height;
}

int Image::get_value(int i, int j)
{
    Scalar s = this->im.at<uchar>(i,j);
    return s.val[0];
}

// Pixels where mask != 0 are copied to a new Image obj
void Image::applyMask(Image mask)
{
    Mat dest;
    this->im.copyTo(dest, mask.get_im());
    this->set_im(dest);
}
void Image::applyMask(Mat mask)
{
    Mat dest;
    this->im.copyTo(dest, mask);
    this->set_im(dest);
}


// subtracts the provided image from this image
void Image::subtract(Image other) 
{
    cv::subtract(this->im, other.get_im(), this->im);
}

// converts this to a new colour (e.g. COLOR_GRAY2BGR)
void Image::convertColour(int new_colour)
{
    cvtColor(this->im, this->im, new_colour);
}

// converts this image to a new type (e.g. CV_8UC1)
void Image::convertType(int new_type)
{
    Mat new_im;
    this->im.convertTo(new_im, new_type);
    this->set_im(new_im);
}   

// for each pixel in this, call func at each point w/ <this->im, image.get_im(), i, j>
void Image::apply(Image image, std::function<void(Mat, Mat, int, int)> func)
{
    int i,j;

    for ( i = 0; i < this->im.rows; i++ ) {
        for ( j = 0; j < this->im.cols; j++ ) {
            func(this->im, image.get_im(), i, j);
        }
    }
}
// for each pixel in this, call func at each point w/ <this->im, i, j>
void Image::apply(std::function<void(Mat, int, int)> func)
{
    int i,j;

    for ( i = 0; i < this->im.rows; i++ ) {
        for ( j = 0; j < this->im.cols; j++ ) {
            func(this->im, i, j);
        }
    }
}

// save the image values to a file
void Image::save_to_csv(std::string filename)
{
    std::ofstream file;
    file.open(filename);

    for ( int i = 0; i < this->im.rows; i++ ) {
        for ( int j = 0; j < this->im.cols; j++ ) {
            file << this->im.at<int>(i,j) << ",";
        }
        file << "\n";
    }

    file.close();
}

void Image::crop(int minx, int miny, int maxx, int maxy)
{
    Mat cropped_im = this->im(Range(miny, maxy), Range(minx, maxx));
    this->im = cropped_im;
}