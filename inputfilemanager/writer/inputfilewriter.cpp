#include <iostream>
#include <stdlib.h>     /* atof */
#include <cmath>

#include "inputfilewriter.h"

#define MIN_MINERAL_VALUE 0.1f
#define MAX_MINERAL_VALUE 5.0f
#define OPTIMAL_PATH_MINERAL_VALUE 50000.0f

#define BINARY_FILE_SUFFIX "_bin"
#define READABLE_FILE_SUFFIX "_readable"

InputFileWriter::InputFileWriter(float baseX, float baseY, int numberOfMinerals, bool optimalPathEnabled, std::string binFilename, std::string readableFilename)
{
    // Create and open the files
    std::ofstream binaryfile;
    binaryfile.open(binFilename.c_str(), std::fstream::out | std::fstream::binary);

    std::ofstream readableFile;
    readableFile.open(readableFilename.c_str(), std::fstream::out);

    Mineral mineral;

    int minimumNumberOfMinerals(0); // used when optimal path enabled
    float stepSize(.0f); // used when optimal path enabled

    if(optimalPathEnabled)
    {
        std::cout << "In order to create the data with a preset optimal path, please enter the step size: ";
        std::cin >> stepSize;

        // Calculate the corresponding grid size
        int gridLength = ceil(baseX/stepSize)+1;
        int gridWidth = ceil(baseY/stepSize)+1;

        minimumNumberOfMinerals = (fmin(gridWidth,gridLength)-1)*2+1; // +1 for mineral at point [0,0]
        if(numberOfMinerals < minimumNumberOfMinerals)
        {
            numberOfMinerals = minimumNumberOfMinerals;

            std::cout << "On order to create the data with a preset optimal path, the number of minerals has been automatically increased to the minimum value of: " <<
                         minimumNumberOfMinerals << std::endl;
        }
    }

    // Initialize mining data
    miningData->baseX = baseX;
    miningData->baseY = baseY;
    miningData->nMinerals = numberOfMinerals;
    miningData->data = (float*) malloc(3*numberOfMinerals*sizeof(float));

    // First write the base station
    mineral.x = baseX;
    mineral.y = baseY;
    mineral.value = .0f;
    writeToBinFile(binaryfile, mineral); // binary file
    writeToReadableFile(readableFile, mineral, true); // readable file

    int mineralsInserted(0);
    if(optimalPathEnabled)
    {
        int gridX(0), gridY(0);
        for(int i = 0; i < minimumNumberOfMinerals; i++, mineralsInserted++)
        {
            mineral.x = gridX*stepSize;
            mineral.y = gridY*stepSize;
            mineral.value = OPTIMAL_PATH_MINERAL_VALUE;

            miningData->data[mineralsInserted*3] = mineral.x;
            miningData->data[mineralsInserted*3+1] = mineral.y;
            miningData->data[mineralsInserted*3+2] = mineral.value;

            writeToBinFile(binaryfile, mineral); // binary file
            writeToReadableFile(readableFile, mineral); // readable file

            if(i%2 == 0)
                gridX++;
            else
                gridY++;
        }
    }

    for(int i = mineralsInserted; i < numberOfMinerals; i++, mineralsInserted++)
    {
        mineral.x = InputFileManager::fRand(baseX);
        mineral.y = InputFileManager::fRand(baseY);
        mineral.value = InputFileManager::fRand(MIN_MINERAL_VALUE,MAX_MINERAL_VALUE);

        miningData->data[mineralsInserted*3] = mineral.x;
        miningData->data[mineralsInserted*3+1] = mineral.y;
        miningData->data[mineralsInserted*3+2] = mineral.value;

        writeToBinFile(binaryfile, mineral); // binary file
        writeToReadableFile(readableFile, mineral); // readable file
    }
}

void InputFileWriter::writeToBinFile(std::ofstream& file, Mineral& mineral)
{
    file.write(reinterpret_cast<char*>(&mineral.x), sizeof(float));
    file.write(reinterpret_cast<char*>(&mineral.y), sizeof(float));
    file.write(reinterpret_cast<char*>(&mineral.value), sizeof(float));
}

void InputFileWriter::writeToReadableFile(std::ofstream& file, Mineral& mineral, bool base)
{
    if(base)
    {
        file << "*********************BASE STATION*********************" << std::endl;
        file << "[ " << mineral.x << "," << mineral.y << "] --> " << mineral.value << std::endl;
        file << "******************************************************" << std::endl;
    }
    else
        file << "[ " << mineral.x << "," << mineral.y << "] --> " << mineral.value << std::endl;
}

// TEST MAIN
#define ARG_BASEX           "-basex"
#define ARG_BASEY           "-basey"
#define ARG_MINERALCOUNT    "-n"
#define ARG_OPTIMALPATH     "-optimalpath"
#define ARG_OUTPUTDIR       "-outputdir"

#define MAX_MINERALS_PRINT  100
#define F_UNSET             -1.f
#define I_UNSET             -1

int main(int argc, char *argv[])
{
    bool optimalPathEnabled(false);
    float baseX(F_UNSET), baseY(F_UNSET);
    int nMinerals(I_UNSET);
    char * outpurDir = NULL;

    int argIdx(1);
    while(argIdx < argc)
    {
        if(std::string(argv[argIdx]) == ARG_BASEX)
        {
            baseX = (float) atof(argv[argIdx+1]);
            argIdx += 2;
        }
        else if(std::string(argv[argIdx]) == ARG_BASEY)
        {
            baseY = (float) atof(argv[argIdx+1]);
            argIdx += 2;
        }
        else if(std::string(argv[argIdx]) == ARG_MINERALCOUNT)
        {
            nMinerals = atoi(argv[argIdx+1]);
            argIdx += 2;
        }
        else if(std::string(argv[argIdx]) == ARG_OPTIMALPATH)
        {
            optimalPathEnabled = true;
            argIdx += 1;
        }
        else if(std::string(argv[argIdx]) == ARG_OUTPUTDIR)
        {
            outpurDir = argv[argIdx+1];
            argIdx += 2;
        }
        else
        {
            InputFileWriter::printUsage();
            return 1;
        }
    }

    if(baseX == F_UNSET || baseY == F_UNSET || nMinerals == I_UNSET || outpurDir == NULL)
    {
        InputFileWriter::printUsage();
        return 1;
    }

    std::string filename(InputFileWriter::generateFilename(baseX, baseY, nMinerals, optimalPathEnabled));
    std::string binFilename(std::string(outpurDir)+"/"+filename+"_bin");
    std::string readableFilename(std::string(outpurDir)+"/"+filename+"_readable");

    std::cout << "**********************ASTRO MINER INPUT FILE GENERATOR**********************" << std::endl;
    std::cout << "----Configuration" << std::endl;
    std::cout << "Base X: " << baseX << std::endl;
    std::cout << "Base Y: " << baseY << std::endl;
    std::cout << "Number of minerals: " << nMinerals << std::endl;
    std::cout << "Output binary file: " << binFilename << std::endl;
    std::cout << "Output readable file: " << readableFilename << std::endl;
    std::cout << "Preset optimal path trigger: " << (optimalPathEnabled ? "on" : "off") << std::endl;
    std::cout << "----" << std::endl;

    InputFileWriter ifWriter(baseX, baseY, nMinerals, optimalPathEnabled, binFilename, readableFilename);
    if(nMinerals < MAX_MINERALS_PRINT)
      ifWriter.getMiningData()->print();

    std::cout << "Completed Succesfully!" << std::endl;
    return 0;
}

void InputFileWriter::printUsage()
{
    std::cout << "Usage: inputFileCreator [OPTIONS] -basex <basex> -basey <basey> -n <mineral_count> -outputdir <outputdir> " << std::endl << std::endl;
    std::cout << "Where OPTIONS: " << std::endl;
    std::cout << "-optimalpath         " << "For testing purposes: minerals are placed along the diagonal with a very big value in order to preset an optimal path." << std::endl;
}

std::string InputFileWriter::generateFilename(float baseX, float baseY, int nMinerals, bool optimalPathEnabled)
{
    std::stringstream ss (std::stringstream::in | std::stringstream::out);
    ss << "BX" << baseX << "_BY" << baseY << "_N" << nMinerals << "_OP" << (optimalPathEnabled ? "on" : "off");
    return ss.str();
}

std::string InputFileWriter::to_string(const float& num, const int& ndigits)
{
    std::stringstream ss (std::stringstream::in | std::stringstream::out);
    ss << num;
    std::string value(ss.str());
    if(value.size() > ndigits)
        value.resize(ndigits);
    return value;
}
