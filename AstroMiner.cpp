#include "AstroMiner.h"
#include "cuda/deviceQuery.h"
#include "inputfilemanager/reader/inputfilereader.h"
#include "cpu/cpuminer.h"

#include <string>
#include <iostream>
#include <stdlib.h>     /* atof */

void AstroMiner::printUsage()
{
    std::cout << "Usage: AstroMiner <input_file> <step_size>" << std::endl;
}

#define ARGS_REQUIRED 3
#define FILENAME_ARG_IDX 1
#define STEP_SIZE_ARG_IDX 2
int main ( int argc, char **argv )
{
    if(argc != ARGS_REQUIRED)
    {
        AstroMiner::printUsage();
        return 1;
    }
    char * inputFile(argv[FILENAME_ARG_IDX]);
    float stepSize = (float) atof(argv[STEP_SIZE_ARG_IDX]);
    std::cout << "Reading in file " << inputFile << "...";
    // First get the base and minerals from the file
    InputFileReader reader;
    if(!reader.parse(inputFile))
    {
        std::cerr << "Unable to parse input file" << std::endl;
        return 1;
    }
    MiningData miningData = reader.getMiningData();
    // CPU MINER
    CPUMiner cpuMiner(miningData, stepSize);
    float bestPathValue(.0f);
    Path bestPath = cpuMiner.findBestPath(bestPathValue);
    std::cout << "****BEST PATH****" << std::endl;
    std::cout << "PATH: "; bestPath.print();
    std::cout << "VALUE: " << bestPathValue << std::endl;
    std::cout << "*****************" << std::endl;
    std::cout << "*****GRID****" << std::endl;
    cpuMiner.getGrid().print();
    std::cout << "**************" << std::endl;
}
