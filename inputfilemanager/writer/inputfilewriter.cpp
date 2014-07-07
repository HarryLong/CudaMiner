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

        int minimumNumberOfMinerals = (fmin(gridWidth,gridLength)-1)*2+1; // +1 for mineral at point [0,0]
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
#define REQUIRED_ARGS_CNT 6
#define BASEX_ARG_IDX 1
#define BASEY_ARG_IDX 2
#define ASTROCOUNT_ARG_IDX 3
#define FILENAME_ARG_IDX 4
#define PRESET_OPTIMAL_PATH_ARG_IDX 5

#define PRESET_OPTIMAL_PATH_ARG "--preset-optimal-path="

#define MAX_MINERALS_PRINT 100

int main(int argc, char *argv[])
{
    if(argc != REQUIRED_ARGS_CNT)
    {
        InputFileWriter::printUsage();
        return 1;
    }

    float baseX((float) atof(argv[BASEX_ARG_IDX]));
    float baseY((float) atof(argv[BASEY_ARG_IDX]));

    int nMinerals(atoi(argv[ASTROCOUNT_ARG_IDX]));
    std::string baseFilename(argv[FILENAME_ARG_IDX]);
    std::string binFilename(baseFilename);
    binFilename += BINARY_FILE_SUFFIX;
    std::string readableFilename(baseFilename);
    readableFilename += READABLE_FILE_SUFFIX;

    bool optimalPathEnabled(false);

    // Figure out whether optimal path is turned on or off
    {
        int constantArgPartLength(std::string(PRESET_OPTIMAL_PATH_ARG).length());

        std::string rawOptimalPathArg(argv[PRESET_OPTIMAL_PATH_ARG_IDX]);
        std::string onOff(rawOptimalPathArg.substr(constantArgPartLength));

        if(onOff == "on" || onOff == "ON" || onOff == "yes" || onOff == "YES")
            optimalPathEnabled = true;
        else if(onOff == "off" || onOff == "OFF" || onOff == "no" || onOff == "NO")
            optimalPathEnabled = false;
        else
        {
            InputFileWriter::printUsage();
            return 1;
        }
    }

    std::cout << "Creating new input file with: " << std::endl;
    std::cout << "Base X: " << baseX << std::endl;
    std::cout << "Base Y: " << baseY << std::endl;
    std::cout << "Number of minerals: " << nMinerals << std::endl;
    std::cout << "Output binary file: " << binFilename << std::endl;
    std::cout << "Output readable file: " << readableFilename << std::endl;
    std::cout << "Preset optimal path trigger: " << (optimalPathEnabled ? "on" : "off") << std::endl;

    InputFileWriter ifWriter(baseX, baseY, nMinerals, optimalPathEnabled, binFilename, readableFilename);
    if(nMinerals < MAX_MINERALS_PRINT)
      ifWriter.getMiningData()->print();

    std::cout << "Completed Succesfully!" << std::endl;
    return 0;
}

void InputFileWriter::printUsage()
{
    std::cout << "Usage: inputFileCreator <baseX> <baseY> <number_of_asteroids> <output_file_name> <--preset-optimal-path=on|off>" << std::endl;
}
