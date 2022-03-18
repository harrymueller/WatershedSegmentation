#include "nuclei_spots.hpp"

void NucleiSpots::nuclei_spots(Mat im, std::string output_dir)
{
    // var declaration
    int val, i, j, id;

    double num_spots = 0; // number of spots incorporated as nuclei
    int num_nuclei = Binning::find_max_bin_id(im); // binning starts at 2 - background was = 1

    // total_x:total_y:num per id
    std::vector<std::vector<uint>> nuclei_tallies(num_nuclei, std::vector<uint>(3, 0));

    // nuclei spots file stream
    std::ofstream nuclei_spots;
    nuclei_spots.open(output_dir + "/nuclei_spots.tsv");

    // header
    nuclei_spots << "# The coords of each spot, and the id of the nuclei they refer to" << std::endl;
    nuclei_spots << "nuclei_id\tx\ty\n";

    // loop through image matrix saving labels
    for ( i = 0; i < im.rows; i++ ) {
        for ( j = 0; j < im.cols; j++ ) {
            val = im.at<int>(i,j);

            if (val > 1) {// val -1 so ids start at 1
                id = val - 2;
                nuclei_spots << id << "\t" << j << "\t" << i << std::endl;

                // add x and y to per-nuclei tallies
                nuclei_tallies[id][0] += j;
                nuclei_tallies[id][1] += i;
                nuclei_tallies[id][2] ++;

                // add to global tallies
                num_spots++;
            }
        }
    }

    nuclei_spots.close();
    
    NucleiSpots::nuclei_coords(num_nuclei, nuclei_tallies, output_dir + "/nuclei_coords.tsv");
    NucleiSpots::stats(num_spots, num_nuclei, nuclei_tallies, output_dir + "/stats.tsv");
}

/*
    Saves average nuclei coords to a file
*/
void NucleiSpots::nuclei_coords(int num_nuclei, std::vector<std::vector<uint>> nuclei_tallies, std::string filename)
{
    // mean coords
    std::ofstream nuclei_coords;
    nuclei_coords.open(filename);

    // header
    nuclei_coords << "# Average coords of each nuclei" << std::endl;
    nuclei_coords << "nuclei_id\tx\ty" << std::endl;;

    for (int i = 0; i < num_nuclei; i++) {
        nuclei_coords << i << "\t" << (nuclei_tallies[i][0] / nuclei_tallies[i][2]) <<
            "\t" << (nuclei_tallies[i][1] / nuclei_tallies[i][2]) << std::endl;
    }

    nuclei_coords.close();
}

/*
    Calculate some basic statistics based on num spots, num nuclei, and nuclei tallies, and output to a file
*/
void NucleiSpots::stats(int num_spots, int num_nuclei, std::vector<std::vector<uint>> nuclei_tallies, std::string filename)
{
    // stats
    std::ofstream stats;
    stats.open(filename);

    double mean_nuclei_size = num_spots / num_nuclei;

    stats << "# Some statistics on nuclei count and sizes" << std::endl <<
        "number_of_nuclei\t" << num_nuclei << std::endl <<
        "mean_nuclei_size\t" << mean_nuclei_size << std::endl;

    // std of nuclei size, max and min sizes
    long double diff_squared = 0;
    int max_nuclei_size = nuclei_tallies[0][2], min_nuclei_size = nuclei_tallies[0][2];

    for (int i = 0; i < num_nuclei; i++) {
        diff_squared += pow((nuclei_tallies[i][2] - mean_nuclei_size), 2);

        if (nuclei_tallies[i][2] > max_nuclei_size) max_nuclei_size = nuclei_tallies[i][2];
        else if (nuclei_tallies[i][2] < min_nuclei_size) min_nuclei_size = nuclei_tallies[i][2];
    }
    stats << "std_nuclei_size\t" << sqrt(diff_squared / num_nuclei) << std::endl <<
        "min_nuclei_size\t" << min_nuclei_size << std::endl <<
        "max_nuclei_size\t" << max_nuclei_size << std::endl;
    stats.close();
}
