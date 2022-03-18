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
#define CLI_OPTIONS "hi:o:g:t:b:c:x:y:"

/*##############################
    FUNCTIONS
##############################*/

enum command_opts {
    CROP = 0,
    WATERSHED = 1,
    BIN = 2
};

class Opts
{
    public:
        // attributes
        std::string input_file;
        std::string output_dir;
        std::string gem_file;

        command_opts cmd;

        int t, b;
        float c;
        int x, y;

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