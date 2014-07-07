#include "AstroMiner.h"
#include "cuda/deviceQuery.h"
#include "inputfilemanager/reader/inputfilereader.h"
#include "cpu/cpuminer.h"
#include "cuda/gpuminer.h"
#include "common/timer.h"

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
    std::cout << "OK!" << std::endl;

    MiningData * miningData = reader.getMiningData();

    Miner * gpuMiner = new GPUMiner(miningData, stepSize);
    Miner * cpuMiner = new CPUMiner(miningData, stepSize);

    Timer timer;
    double time(.0);

//    // CPU MINER
    timer.start();
    cpuMiner->performBinning();
    time = timer.stop();
    std::cout << "CPU Binning: " << time << std::endl;
//    std::cout << "*****GRID****" << std::endl;
    cpuMiner->getGrid().writeToFile("/home/harry/tmp/cpugrid.txt");
//    std::cout << "**************" << std::endl;

//    // GPU MINER
    timer.start();
    gpuMiner->performBinning();
    time = timer.stop();
    std::cout << "GPU Binning: " << time << std::endl;
//    std::cout << "*****GRID****" << std::endl;
    gpuMiner->getGrid().writeToFile("/home/harry/tmp/gpugrid.txt");
//    std::cout << "**************" << std::endl;
}
