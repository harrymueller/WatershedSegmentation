#include "opts.hpp"

/*
    Sorts through parameters, checking that all req params are supplied, and returns Opts obj
*/
Opts::Opts(int argc, char *argv[])
{
    int option;
    opterr = 0;

    // if no args passed
    if (argc == 1) {
        usage();
        exit(EXIT_FAILURE);
    }

    // convert first arg to string
    std::string command_str = std::string(argv[1]);

    // check what command and set opts
    if (command_str.compare(std::string("crop")) == 0)
        this->cmd = CROP;
    else if (command_str.compare(std::string("watershed")) == 0)
        this->cmd = WATERSHED;
    else if (command_str.compare(std::string("bin")) == 0)
        this->cmd = BIN;
    else if (command_str.compare(std::string("help")) == 0) {
        this->usage();
        exit(EXIT_SUCCESS);
    } else {
        this->usage(std::string("Unrecognised command '") + std::string(argv[1]) + std::string("'."));
        exit(EXIT_FAILURE);
    }

    // set defaults
    this->set_defaults();

    // get dashed options
    while((option = getopt(argc, argv, CLI_OPTIONS)) != -1) {
        switch (option) {
            case 'h': 
                this->usage();
                exit(EXIT_SUCCESS);
            case 'i':
                this->input_file = std::string(optarg);
                break;
            case 'o':
                this->output_dir = std::string(optarg);
                break;
            case 'g':
                this->gem_file = std::string(optarg);
                break;
            case 't': 
                this->t = atoi(optarg);
                break;
            case 'b': 
                this->b = atoi(optarg);
                break;
            case 'x': 
                this->x = atoi(optarg);
                break;
            case 'y': 
                this->y = atoi(optarg);
                break;
            case 'c': 
                this->c = atof(optarg);
                break;
            default: 
                std::cout << "Unknown argument supplied.\n" << std::endl;
                usage();
                exit(EXIT_FAILURE);
        }
    }

    // check inputs
    switch (this->validate_inputs()) {
        case 0:
            break;
        case 1:
            this->usage("Please pass valid input image file.");
            exit(EXIT_FAILURE);
        case 2:
            this->usage("Please pass valid output dir.");
            exit(EXIT_FAILURE);
        case 3:
            this->usage("Please pass valid GEM file.");
            exit(EXIT_FAILURE);
    }

    // create subdirectory
    if (!this->add_sub_dir()) {
        this->usage("Could not create a subdirectory.");
        exit(EXIT_FAILURE);
    }
}

void Opts::usage(std::string opt_message)
{
    if (!opt_message.empty()) 
        std::cout << opt_message << std::endl << std::endl;
    
    std::cout << "Usage: nuclei_segregation CMD -i: -o: [OPTIONS]" << std::endl << std::endl;
    std::cout << "CMD: crop" << std::endl <<
                 "\tCrops the given image based on the threshold and buffer given." << std::endl <<
                 "\t> crop -i: -o: [-t 150] [-b 128]" << std::endl << std::endl;

    std::cout << "CMD: watershed" << std::endl <<
                 "\tApplies a global threshold (t), a gaussian threshold (b and c), then applies the watershed algorithm for segmentation." << std::endl <<
                 "\t> watershed -i: -o: [-t 100] [-b 41] [-c 0.03]" << std::endl << std::endl;

    std::cout << "CMD: bin" << std::endl <<
                 "\tNOT IMPLEMENTED" << std::endl <<
                 "\t> bin -i: -g: -o: [-x 0] [-y 0]" << std::endl << std::endl;
}

void Opts::set_defaults()
{
    // setting defaults
    if (this->cmd == CROP) {
        this->t = 150; this->b = 128;
    } else if (this->cmd == WATERSHED) {
        this->t = 100, this->b = 41; this->c = 0.03;
    } else if (this->cmd == BIN) {
        this->x = 0; this->y = 0;
    }

    this->input_file = ""; this->output_dir = ""; this->gem_file = "";
}

/*
    validates input_file, output_dir, (and gem if neccessary)
    returns 0 if good, 1 if input bad, 2 if dir is bad, 3 if gem is bad
*/
int Opts::validate_inputs()
{
    // input image
    if (this->input_file.empty() || !std::filesystem::exists(this->input_file)) {
        return 1;
    }
    
    // output dir
    else if (this->output_dir.empty() || !std::filesystem::exists(this->output_dir)) {
        return 2;
    }
    // gem file if cmd is BIN
    else if (this->cmd == BIN) {
        if (this->gem_file.empty() || !std::filesystem::exists(this->gem_file)) {
            return 3;
        }
    }

    return 0;
}

bool Opts::add_sub_dir()
{
    // make output dir
    if (this->cmd == CROP) this->output_dir = this->output_dir + "/01_cropping";
    else if (this->cmd == WATERSHED) this->output_dir = this->output_dir + "/02_watershed";
    else if (this->cmd == BIN) this->output_dir = this->output_dir + "/03_binning";
    
    if (std::filesystem::exists(this->output_dir)) return true;
    else return (mkdir(this->output_dir.c_str(), 0700) == 0);
    //return std::filesystem::create_directory(this->output_dir, 0666);
}