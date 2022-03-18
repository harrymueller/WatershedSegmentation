#include "gem.hpp"

void GEM::gem(Mat im, Opts opts)
{
    // int vars
    int max_bin_id = Binning::find_max_bin_id(im);
    //int x_offset = opts.x, y_offset = opts.y, id, x, y;
    int id, i;
    //int width = im.size().width; int height = im.size().height;

    // vector to hold counts of a given gene
    std::vector<uint> counts;
    // string placeholders
    std::string current_gene = "", new_gene;
    std::string output_file = opts.output_dir + "/nuclei.gem";

    GEM::add_header_to_output(output_file);

    // get gem
    int dims[4] = {opts.x, opts.y, opts.x + im.size().width, opts.y + im.size().height};
    std::vector<GEMLine> gem = GEM::read_gem(opts.gem_file, dims);
    
    /*std::ofstream tempfile;
    tempfile.open(opts.output_dir + "/temp.gem");

    for (int i = 1; i < gem.size(); i++) {
        if (gem[i].gene.compare(gem[i-1].gene) < 0) std::cout << "broken" << std::endl;
        tempfile << gem[i].gene << std::endl;
    }

    tempfile.close();*/
    
    // for each row in GEM
    for (i = 0; i < gem.size(); i++) {
        if (current_gene.empty()) { // start
            current_gene = gem[i].gene;
            counts = std::vector<uint>(max_bin_id, 0);
        } else if (gem[i].gene.compare(current_gene) != 0) {
            GEM::save_genes(current_gene, output_file, max_bin_id, counts);
            counts = std::vector<uint>(max_bin_id, 0);
            current_gene = gem[i].gene;
        }

        //gem[i].x = gem[i].x - opts.x; gem[i].y = gem[i].y - opts.y;
        //if (gem[i].x >= 0 && gem[i].x < im.size().width && gem[i].y >= 0 && gem[i].y <= im.size().height) {
        id = im.at<int>(gem[i].x - opts.x, gem[i].y - opts.y) - 2;
        if (id >= 0) counts[id] += gem[i].count;
        //}
    } 

    GEM::save_genes(current_gene, output_file, max_bin_id, counts);
    


    // open gem file and check that it is valid
    /*std::fstream file(gem_file);
    if (!file.is_open()) {
        std::cout << "Could not open file '" << gem_file << "'\n";
        exit(EXIT_FAILURE);
    }

    std::vector<uint> row;
    std::string l, val;

    // for each row in GEM - read line by line
    std::getline(file, l); // clear first line;
    while (std::getline(file, l)) {
        row.clear();

        std::stringstream temp(l);
        std::getline(temp, new_gene, '\t'); // update new_gene
        while (std::getline(temp, val, '\t')) // add x,y,MIDCount
            row.push_back(atoi(val.c_str()));

        // if new gene: save then reset counts (GEM::save_genes + counts.swap(max_bin_id))
        if (current_gene.empty()) {
            current_gene = new_gene;
            counts = std::vector<uint>(max_bin_id, 0);
        } else if (new_gene.compare(current_gene) != 0 && !current_gene.empty()) {
            GEM::save_genes(current_gene, output_file, max_bin_id, counts);
            counts = std::vector<uint>(max_bin_id, 0);
            current_gene = new_gene;
        }

        // add MIDCount to correct item (based on x and y)
        x = row[0] - x_offset; y = row[1] - y_offset;
        if (x >= 0 && x < width && y >= 0 && y <= width) {
            id = im.at<int>(x, y) - 2;
            if (id >= 0) counts[id] += row[2];
        }
    }*/
}

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

bool GEM::comp(GEMLine a, GEMLine b) {
    return (a.gene.compare(b.gene) < 0);
}

void GEM::add_header_to_output(std::string filename)
{
    std::ofstream file;
    file.open(filename);

    file << "geneID\tnucleiID\tMIDCount" << std::endl;

    file.close();
}

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

GEMLine::GEMLine()
{

}
