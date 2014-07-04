#include <iostream>
#include <stdlib.h>     /* atof */
#include <cmath>

#include "inputfilewriter.h"

#define MIN_MINERAL_VALUE 0.1f
#define MAX_MINERAL_VALUE 5.0f
#define OPTIMAL_PATH_MINERAL_VALUE 50000.0f

InputFileWriter::InputFileWriter(float baseX, float baseY, int numberOfMinerals, bool optimalPathEnabled) : InputFileManager(baseX,baseY)
{
    int mineralsInserted(0);
    if(optimalPathEnabled)
    {
        float stepSize;
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

        int gridX(0), gridY(0);
        for(int i = 0; i < minimumNumberOfMinerals; i++, mineralsInserted++)
        {
            float mineralX = gridX*stepSize;
            float mineralY = gridY*stepSize;

            if(i%2 == 0)
                gridX++;
            else
                gridY++;

            miningData.minerals.push_back(Mineral(mineralX,mineralY,OPTIMAL_PATH_MINERAL_VALUE));
        }
    }
    for(int i = mineralsInserted; i < numberOfMinerals; ++i)
    {
        float x = InputFileManager::fRand(baseX);
        float y = InputFileManager::fRand(baseY);
        float value = InputFileManager::fRand(MIN_MINERAL_VALUE,MAX_MINERAL_VALUE);

        miningData.minerals.push_back(Mineral(x,y,value));
    }
}

void InputFileWriter::writeToFile(std::string filename, FILE_TYPE fileType)
{
    std::ofstream outFile;
    outFile.open(filename.c_str(), fileType == HUMAN_READABLE ? (std::fstream::out) : (std::fstream::out | std::fstream::binary));

    // First write the base station coordinate
    if(fileType == HUMAN_READABLE)
    {
        outFile << "Base Station: [" << miningData.base.x << "," << miningData.base.y << "]" << std::endl;
    }
    else
    {
        // First write the base station coordinate
        writeFloat(outFile, miningData.base.x);
        writeFloat(outFile, miningData.base.y);
        float zero(0);
        writeFloat(outFile, zero);
    }


    for(std::vector<Mineral>::iterator it = miningData.minerals.begin(); it != miningData.minerals.end(); it++)
    {
        if(fileType == HUMAN_READABLE)
        {
            outFile << "[" << it->x << "," << it->y << "] --> " << it->value << std::endl;
        }
        else
        {
            writeFloat(outFile, it->x);
            writeFloat(outFile, it->y);
            writeFloat(outFile, it->value);
        }
    }
    outFile.close();
}

void InputFileWriter::writeFloat(std::ofstream& file, float& value)
{
    file.write(reinterpret_cast<char*>(&value), sizeof(float));
}

// TEST MAIN
#define REQUIRED_ARGS_CNT 6
#define BASEX_ARG_IDX 1
#define BASEY_ARG_IDX 2
#define ASTROCOUNT_ARG_IDX 3
#define FILENAME_ARG_IDX 4
#define PRESET_OPTIMAL_PATH_ARG_IDX 5

#define PRESET_OPTIMAL_PATH_ARG "--preset-optimal-path="

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
    char* filename(argv[FILENAME_ARG_IDX]);
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
    std::cout << "Output file: " << filename << std::endl;
    std::cout << "Preset optimal path trigger: " << (optimalPathEnabled ? "on" : "off") << std::endl;

    std::string binFilename(filename);
    binFilename += "_bin";

    std::string humanReadableFilename(filename);
    humanReadableFilename += "_humanreadable";

    InputFileWriter ifWriter(baseX, baseY, nMinerals, optimalPathEnabled);
    ifWriter.printMinerals();
    ifWriter.writeToFile(binFilename, BINARY);
    ifWriter.writeToFile(humanReadableFilename, HUMAN_READABLE);
    return 0;
}

void InputFileWriter::printUsage()
{
    std::cout << "Usage: inputFileCreator <baseX> <baseY> <number_of_asteroids> <output_file_name> <--preset-optimal-path=on|off>" << std::endl;
}
