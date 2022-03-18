#include "image.hpp"
#include "io.hpp"

#include <stdio.h>
#include <iostream>
#include <fstream>

namespace BinGenes
{
    void bin_genes(Mat, std::string);
    void empty_array(int*, int);
    void save_genes(std::string, std::string, int*, int);
}