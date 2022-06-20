#include "gem.hpp"

void GEM::gem(Mat im, Opts opts)
{
    // number of bin ids
    int max_bin_id = Binning::find_max_bin_id(im);
    // decl ints
    int id, i;

    // vector to hold counts of a given gene
    std::vector<uint> counts;

    // string placeholders
    std::string current_gene = "", new_gene;
    std::string output_file = opts.output_dir + "/nuclei.gem";

    GEM::add_header_to_output(output_file);

    // get gem
    int dims[4] = {opts.x, opts.y, opts.x + im.size().width, opts.y + im.size().height};
    std::vector<GEMLine> gem = GEM::read_gem(opts.gem_file, dims);
    
    // for each row in GEM
    for (i = 0; i < gem.size(); i++) {
        if (current_gene.empty()) { // start
            current_gene = gem[i].gene;
            counts = std::vector<uint>(max_bin_id, 0);
        } else if (gem[i].gene.compare(current_gene) != 0) { // if same gene as prev
            GEM::save_genes(current_gene, output_file, max_bin_id, counts);
            counts = std::vector<uint>(max_bin_id, 0);
            current_gene = gem[i].gene;
        }

        // get id by taking the cluster id and removing two
        id = im.at<int>(gem[i].x - opts.x, gem[i].y - opts.y) - 2;
        if (id >= 0) counts[id] += gem[i].count; // if a valid nuclei id -> add to counts
    } 

    GEM::save_genes(current_gene, output_file, max_bin_id, counts);
}

/*
    reads in GEM file, returning a vector of GEMLine objs that contain the data from each line
*/
std::vector<GEMLine> GEM::read_gem(std::string gem_file, int *dims)
{
    std::vector<GEMLine> gem;
    GEMLine current = GEMLine();
    int x,y;

    // open gem file and check that it is valid
    std::fstream file(gem_file);
    if (!file.is_open()) {
        std::cout << "Could not open file '" << gem_file << "'\n";
        exit(EXIT_FAILURE);
    }

    std::string l;

    // read line by line
    std::getline(file, l); // clear first line;
    while (std::getline(file, l)) {
        current = GEMLine(l);

        if (current.x >= dims[0] && current.x <= dims[2] && 
            current.y >= dims[1] && current.y <= dims[3])
                gem.push_back(current);
    }

    // sort
    std::sort(gem.begin(), gem.end(), GEM::comp);
    return gem;
}

/*
    FN to sort vector of GEMLines
*/
bool GEM::comp(GEMLine a, GEMLine b) {
    return (a.gene.compare(b.gene) < 0);
}

/*
    Opens output GEM file and heads a head
*/
void GEM::add_header_to_output(std::string filename)
{
    std::ofstream file;
    file.open(filename);

    file << "geneID\tnucleiID\tMIDCount" << std::endl;

    file.close();
}

/*
    Given a gene and a vector of counts, outputs id, gene, and count for each entry in counts that is not 0 (remains sparse)
*/
void GEM::save_genes(std::string gene, std::string filename, int max_bin_id, std::vector<uint> counts) 
{
    std::ofstream file;
    file.open(filename, std::ios_base::app);

    for ( int id = 0; id < max_bin_id; id++ ) {
        if (counts[id] > 0)
            file << gene << "\t" << id << "\t" << counts[id] << "\n";
    }

    file.close();
}

/*
    GEMLine constructor that takes a string
*/
GEMLine::GEMLine(std::string line)
{
    std::string temp_str;
    std::stringstream temp(line);
    
    std::getline(temp, temp_str, '\t');
    this->gene = temp_str;

    std::getline(temp, temp_str, '\t');
    this->x = atoi(temp_str.c_str());
    std::getline(temp, temp_str, '\t');
    this->y = atoi(temp_str.c_str());
    std::getline(temp, temp_str, '\t');
    this->count = atoi(temp_str.c_str());
}

/* 
    empty GEMLine constructor
*/
GEMLine::GEMLine() {}