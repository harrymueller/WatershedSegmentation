#include "nuclei_segregation.hpp"

/* TODO erode seeds?
    Q. erode seeds?
    Improve algo
    Improve UI
    Improve opts passing
    Q. WTF did unknown do previously???
    Rename seeds / markers to be consistant
    marker type is int -> may be problem if >2**31-1 nuclei
    improve apply image to take lots of variables and pass to function
    bin ids starting from 0?
    use either tsv or csv consistantly
    improve namespaces
    verbosity option
    convert mean -> median for binning?
    swap vectors w/ arrays
*/



int main(int argc, char *argv[])
{
    // params
    Opts opts = Opts(argc, argv);

    if (opts.cmd == CROP)
        Cropping::crop(opts);
    if (opts.cmd == WATERSHED)
        Watershed::watershed(opts);
    if (opts.cmd == BIN)
        Binning::bin(opts);
    if (opts.cmd == PLOT)
        Plotting::plot_wrapper(opts);


    exit(EXIT_SUCCESS);
}

