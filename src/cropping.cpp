#include "cropping.hpp"

/* threshold image then crop, while saving dimensions */
void Cropping::crop(Opts opts)
{
    std::cout << "Cropping image..." << std::endl;

    // read image
    Image orig(opts.input_file);

    // array of [orig x, orig y, min x, min y, max x, max y]
    int dims[6] = {orig.width(), orig.height(), orig.width(), orig.height(), -1, -1};

    // search image for min, max x and y vals
    for ( int i = 0; i < dims[0]; i++ ) {
        for ( int j = 0; j < dims[1]; j++ ) {
            if (orig.get_value(j,i) > opts.t) 
                Cropping::compare_pos(i, j, dims);
            
        }
    }

    // crop image
    Cropping::add_buffer(dims, opts.b);
    
    orig.crop(dims[2], dims[3], dims[4], dims[5]);
    orig.save(opts.output_dir + "/cropped.png");

    Cropping::save_dim(dims, opts.output_dir + "/cropping_dims.tsv");

    std::cout << "Finished cropping image to a size of " << dims[4] - dims[2] << "x" << dims[5] - dims[3] << "px" << std::endl;
}

/* given an x and y coord, checks if y<miny, y>maxy, x<minx, x>maxx, and adds to dims */
void Cropping::compare_pos(int x, int y, int *dims) 
{
    if (x < dims[2]) dims[2] = x;
    else if (x > dims[4]) dims[4] = x;

    if (y < dims[3]) dims[3] = y;
    else if (y > dims[5]) dims[5] = y;
}

void Cropping::add_buffer(int *dims, int buffer)
{
    // add buffer
    dims[2] -= buffer; dims[3] -= buffer;
    dims[4] += buffer; dims[5] += buffer;

    // ensure min x and y aren't <0
    if (dims[2] < 0) dims[2] = 0;
    if (dims[3] < 0) dims[3] = 0;

    // ensure max x and y don't excede dimensions
    if (dims[4] > dims[0]) dims[4] = dims[0];
    if (dims[5] > dims[1]) dims[5] = dims[1];
}

void Cropping::save_dim(int *dims, std::string filename)
{
    std::ofstream file;
    file.open(filename);

    file << "x\ty\tmin_x\tmin_y\tmax_x\tmax_y\n";
    for (int i = 0; i < 6; i++) {
        file << dims[i];

        if (i < 5) file << "\t";
        else file << "\n";
    }

    file.close();
}