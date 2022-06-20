#include "plotting.hpp"

void Plotting::plot_wrapper(Opts opts)
{
    // got nuclei ids
    std::cout << "Reading markers csv..." << std::endl;
    Mat im = Binning::read_markers(opts.input_file);

    int max_bin_id = Binning::find_max_bin_id(im) + 1;


    if (opts.by_spots) {
        // plot by spot
    } else {
        // read values
        std::vector<int> values = Plotting::read_plot_tsv(opts.plot_file, max_bin_id, opts.plot_type);
    }
}

// given a tsv of <id>\t<val>, create a vector containing all values
std::vector<int> Plotting::read_plot_tsv(std::string filename, int max_bin_id, plot_types plt)
{
    // array
    std::vector<int> values = std::vector<int>(max_bin_id);

    // template variables
    std::string l;
    IdVal idval;

    // open file and check that it is valid
    std::fstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file '" << filename << "'\n";
        exit(EXIT_FAILURE);
    }

    std::getline(file, l);
    // read line by line
    while (std::getline(file, l)) {
        idval = string_to_int(l, plt);
        //std::cout << idval.id << " " << idval.val << std::endl;
        values[idval.id] = idval.val;
    }

    return values;
}

IdVal Plotting::string_to_int(std::string line, plot_types plt)
{
    uint id;
    int val = 0, v;

    std::string idS, valS;
    std::stringstream temp(line);

    getline(temp, idS, '\t');
    id = atoi(idS.c_str());
    
    if (plt < 2) { // single value
        getline(temp, valS, '\t');
        val = atoi(valS.c_str());
    } else { // rgb - use 1 int to store 3x 8bit ints
        for (int i = 0; i < 3; i++) {
            getline(temp, valS, '\t');
            v = atoi(valS.c_str());

            val = (val << 8) + v; // shift int 8 left, then add next val
        }
    }
    
    return IdVal(id, val);
}
//std::vector<uint> Plotting::min_max_scaling(std::vector<uint>)

IdVal::IdVal(int id, int val)
{
    this->id = id;
    this->val = val;
}
IdVal::IdVal(){}