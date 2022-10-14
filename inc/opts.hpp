#ifndef OPTS_
#define OPTS_

/*##############################
    LIBRARIES
##############################*/
#include <iostream>
#include <string>
#include <getopt.h>
#include <filesystem>

#include <sys/stat.h>

/*##############################
    PREPROCESSOR VARIABLES
##############################*/
#define CLI_OPTIONS "hi:o:g:p:t:b:c:x:y:sn"

/*##############################
    FUNCTIONS
##############################*/

enum command_opts {
    CROP = 0,
    THRESHOLD = 1,
    WATERSHED = 2,
    BIN = 3,
    PLOT = 4
};

enum plot_types {
    VALUES = 0,
    GREYSCALE = 1,
    RGB = 2
};

class Opts
{
    public:
        // attributes
        std::string input_file;
        std::string output_dir;
        std::string gem_file;
        std::string plot_file;

        command_opts cmd;

        int t, b;
        float c;
        int x, y;

        plot_types plot_type;
        bool by_spots;

        // constructor
        Opts(int, char*[]);

    private:
        // methods
        void usage(std::string opt_message = "");
        void set_defaults();
        int validate_inputs();
        bool add_sub_dir();
};

#endif