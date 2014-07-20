#include "AstroMiner.h"
#include "inputfilemanager/reader/inputfilereader.h"
#include "cpu/cpuminer.h"
#include "cuda/gpuminer.h"

#include <string>
#include <iostream>
#include <stdlib.h>     /* atof */

#define CPU_DIR "/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/output_files/cpu/"
#define GPU_DIR "/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/output_files/gpu/"

void AstroMiner::printUsage()
{
    std::cout << "Usage: AstroMiner [OPTIONS] -inputfile <filename> -stepsize <stepsize> -outputfile <outputfile>" << std::endl << std::endl;
    std::cout << "Where OPTIONS: " << std::endl;
    std::cout << "-summaryfile         " << "Specify a full path to a file and the program will write summary statistics to the file." << std::endl;
    std::cout << "-runcount            " << "The program will execute the miners n times and average the statistical data on all runs." << std::endl;
}

double writeToSummaryFile( std::ofstream& summaryFile, const SummaryData& summaryData)
{
    // COMMON
    summaryFile << summaryData.gridLength << "," << summaryData.nMinerals << "," << summaryData.cpuSummary.optimalPath << ",";

    //CPU
    summaryFile << summaryData.cpuSummary.binning << "," << summaryData.cpuSummary.aggregation << ",";

    //GPU
    summaryFile << summaryData.gpuSummary.binning << "," << summaryData.gpuSummary.mineralAllocation << "," << summaryData.gpuSummary.mineralCopy << "," <<
                   summaryData.gpuSummary.mineralFree << "," << summaryData.gpuSummary.gridAllocation << "," <<
                   summaryData.gpuSummary.gridMemset << "," << summaryData.gpuSummary.gridPadding << "," << summaryData.gpuSummary.binningKernel << "," <<
                   summaryData.gpuSummary.aggregation << "," << summaryData.gpuSummary.accumulationKernel << "," << summaryData.gpuSummary.gridRetrieval << ",";

    summaryFile << std::endl;
}

#define SUMMARY_FILE_HEADER "G Length, # Minerals, Optimal path, CPU Binning, CPU Aggregation, GPU Binning, GPU mineralAllocation,"

double writeSummaryHeading(std::ofstream& summaryFile)
{
    summaryFile << "G Length, # Minerals, Optimal path, CPU Binning, CPU Aggregation, GPU Binning, GPU mineral allocation, GPU mineral copy, "
                   "GPU mineral free, GPU grid allocation, GPU grid memset, GPU grid padding, GPU binning kernel, GPU Aggregation, GPU accumulation kernel, "
                   "GPU grid retrieval"<< std::endl;

}

//  float mineralAllocation, mineralCopy, mineralFree, gridAllocation, gridMemset, gridPadding, binningKernel, accumulationKernel, gridRetrieval;

//    float binning, aggregation, optimalPath;


#define ARG_SUMMARYFILE "-summaryfile"
#define ARG_INPUTFILE   "-inputfile"
#define ARG_STEPSIZE    "-stepsize"
#define ARG_RUNCOUNT    "-runcount"
#define ARG_OUTPUTFILE  "-outputfile"
#define STEPSIZE_UNSET -1.f

int main ( int argc, char **argv )
{    
    bool summarize(false);
    char* summaryFilename = NULL;
    char* inputFilename = NULL;
    char* outputFilename = NULL;
    float stepsize(STEPSIZE_UNSET);
    int runCount(1);

    int argIdx(1);
    while(argIdx < argc)
    {
        if(std::string(argv[argIdx]) == ARG_INPUTFILE)
        {
            inputFilename = argv[argIdx+1];
        }
        else if(std::string(argv[argIdx]) == ARG_SUMMARYFILE)
        {
            summaryFilename = argv[argIdx+1];
            summarize = true;
        }
        else if(std::string(argv[argIdx]) == ARG_STEPSIZE)
        {
            stepsize = (float) atof(argv[argIdx+1]);
        }
        else if(std::string(argv[argIdx]) == ARG_RUNCOUNT)
        {
            runCount = atoi(argv[argIdx+1]);
        }
        else if(std::string(argv[argIdx]) == ARG_OUTPUTFILE)
        {
            outputFilename = argv[argIdx+1];;
        }
        else
        {
            AstroMiner::printUsage();
            return 1;
        }
        argIdx += 2;
    }

    if(inputFilename == NULL || stepsize == STEPSIZE_UNSET || outputFilename == NULL)
    {
        AstroMiner::printUsage();
        return 1;
    }

    std::ofstream summaryFile;
    SummaryData summaryData;

    // First get the base and minerals from the file
    InputFileReader reader;
    if(!reader.parse(inputFilename))
    {
        std::cerr << "Unable to parse input file" << std::endl;
        return 1;
    }

    if(summarize)
    {
        summaryFile.open(summaryFilename, std::fstream::out|std::fstream::app);
        if(!summaryFile.is_open())
        {
            std::cerr << "Unable to open file: " << summaryFilename << std::endl;
            return 1;
        }
        if(summaryFile.tellp() == 0) // write the header the file is empty
            writeSummaryHeading(summaryFile);
    }

    // Ensure the output file is valid
    {
        std::ofstream outputFile;
        outputFile.open(outputFilename, std::fstream::out);
        if(!outputFile.is_open())
        {
            std::cerr << "Unable to open file: " << outputFilename << std::endl;
            return 1;
        }
    }

    std::cout << "**********************ASTRO MINER**********************" << std::endl;
    std::cout << "----Configuration" << std::endl;
    std::cout << "Input file: " << inputFilename << std::endl;
    std::cout << "Step size: " << stepsize << std::endl;
    std::cout << "Run count: " << runCount << std::endl;
    std::cout << "Output file: " << outputFilename << std::endl;
    std::cout << "Write summary to file: ";
    if(summarize)
        std::cout << "enabled (" << summaryFilename << ")" << std::endl;
    else
        std::cout << "disabled" << std::endl;
    std::cout << "----" << std::endl;

    MiningData * miningData = reader.getMiningData();
    GPUMiner * gpuMiner = NULL;
    CPUMiner * cpuMiner = NULL;

    for(int i = 0; i < runCount; i++)
    {
        std::cout << "Performing run " << (i+1) << " of " << runCount <<  "..." << std::endl;

        if(gpuMiner != NULL)
            delete gpuMiner;

        if(cpuMiner != NULL)
            delete cpuMiner;

        gpuMiner = new GPUMiner(miningData, stepsize);
        cpuMiner = new CPUMiner(miningData, stepsize);

        // CPU MINER
        std::cout << "Mining on CPU...";
        cpuMiner->performBinning();
        cpuMiner->createAccumulatedGrid();
        cpuMiner->calculateBestPath();
        summaryData.cpuSummary.add(cpuMiner->getRunSummary());
        std::cout << "complete!" << std::endl;


        // GPU MINER
        std::cout << "Mining on GPU...";
        gpuMiner->performBinning();
        gpuMiner->createAccumulatedGrid();
        gpuMiner->calculateBestPath();
        summaryData.gpuSummary.add(gpuMiner->getRunSummary());
        std::cout << "complete!" << std::endl;

        //CPU & GPU
        summaryData.equal = summaryData.equal && cpuMiner->getOptimalPath().equals(gpuMiner->getOptimalPath());

        std::cout << "Run " << (i+1) << " of " << runCount <<  " complete!" << std::endl;
        std::cout << "----" << std::endl;
    }

    summaryData.gridLength = cpuMiner->getGrid().length;
    summaryData.nMinerals = miningData->nMinerals;
    summaryData.cpuSummary.average(runCount);
    summaryData.gpuSummary.average(runCount);

    if(summarize)
    {
        writeToSummaryFile(summaryFile, summaryData);
        summaryFile.close();
    }

    std::cout << "---------------------------------SUMMARY---------------------------------------" << std::endl;
    std::cout << "**********CPU**********" << std::endl;
    std::cout << "Binning: " << summaryData.cpuSummary.binning<< std::endl;
    std::cout << "Aggregation: " << summaryData.cpuSummary.aggregation << std::endl;
    std::cout << "**********GPU**********" << std::endl;
    std::cout << "Binning: " << summaryData.gpuSummary.binning << std::endl;
    std::cout << "-- Mineral allocation: " << summaryData.gpuSummary.mineralAllocation << std::endl;
    std::cout << "-- Mineral copy: " << summaryData.gpuSummary.mineralCopy << std::endl;
    std::cout << "-- Mineral free: " << summaryData.gpuSummary.mineralFree << std::endl;
    std::cout << "-- Grid allocation: " << summaryData.gpuSummary.gridAllocation << std::endl;
    std::cout << "-- Grid memset: " << summaryData.gpuSummary.gridMemset << std::endl;
    std::cout << "-- Grid padding: " << summaryData.gpuSummary.gridPadding << std::endl;
    std::cout << "-- Binning kernel: " << summaryData.gpuSummary.binningKernel<< std::endl;
    std::cout << "Aggregation: " << summaryData.gpuSummary.aggregation << std::endl;
    std::cout << "-- Accumulation kernel: " << summaryData.gpuSummary.accumulationKernel << std::endl;
    std::cout << "-- Grid retrieval: " << summaryData.gpuSummary.gridRetrieval << std::endl;
    std::cout << "**********MIXED********" << std::endl;
    std::cout << "Optimal path: " << summaryData.cpuSummary.optimalPath << std::endl;
    std::cout << "Optimal path equal: " << (summaryData.equal ? "Yes" : "No") << std::endl;
    std::cout << "-------------------------------------------------------------------------------" << std::endl;

    cpuMiner->getOptimalPath().writeToFile(outputFilename, stepsize);
}
