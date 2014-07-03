#include <iostream>

#include "inputfilereader.h"

#define FILENAME_ARG_IDX 1
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage: readinputFile <input_file_name>" << std::endl;
        return 1;
    }

    char* filename = argv[FILENAME_ARG_IDX];

    std::cout << "Reading in input file: " << filename << std::endl;

    InputFileReader reader(filename);
    reader.printMinerals();
    return 0;
}


