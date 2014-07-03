#include <iostream>
#include <stdlib.h>     /* atof */

#include "inputfilewriter.h"

#define MIN_MINERAL_VALUE 0.1f
#define MAX_MINERAL_VALUE 5.0f

InputFileWriter::InputFileCreator(float baseX, float baseY, int numberOfMinerals) : InputFileManager(baseX,baseY)
{
    for(int i = 0; i < numberOfMinerals; ++i)
    {
        float x = InputFileManager::fRand(baseX);
        float y = InputFileManager::fRand(baseY);
        float value = InputFileManager::fRand(MIN_MINERAL_VALUE,MAX_MINERAL_VALUE);

        minerals.push_back(Mineral(x,y,value));
    }
}

void InputFileWriter::writeToFile(std::string filename, FILE_TYPE fileType)
{
    std::ofstream outFile;
    outFile.open(filename.c_str(), fileType == HUMAN_READABLE ? (std::fstream::out) : (std::fstream::out | std::fstream::binary));

    // First write the base station coordinate
    if(fileType == HUMAN_READABLE)
    {
        outFile << "Base Station: [" << baseX << "," << baseY << "]" << std::endl;
    }
    else
    {
        // First write the base station coordinate
        writeFloat(outFile, baseX);
        writeFloat(outFile, baseX);
        float zero(0);
        writeFloat(outFile, zero);
    }


    for(std::vector<Mineral>::iterator it = minerals.begin(); it != minerals.end(); it++)
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
#define BASEX_ARG_IDX 1
#define BASEY_ARG_IDX 2
#define ASTROCOUNT_ARG_IDX 3
#define FILENAME_ARG_IDX 4

int main(int argc, char *argv[])
{
    if(argc != 5)
    {
        std::cout << "Usage: inputFileCreator <baseX> <baseY> <number_of_asteroids> <output_file_name>" << std::endl;
        return 1;
    }

    float baseX = (float) atof(argv[BASEX_ARG_IDX]);
    float baseY = (float) atof(argv[BASEY_ARG_IDX]);
    int number = atoi(argv[ASTROCOUNT_ARG_IDX]);
    char* filename = argv[FILENAME_ARG_IDX];

    std::cout << "Creating new input file with: " << std::endl;
    std::cout << "Base X: " << baseX << std::endl;
    std::cout << "Base Y: " << baseY << std::endl;
    std::cout << "Number of asteroids: " << number << std::endl;
    std::cout << "Output file: " << filename << std::endl;

    std::string binFilename(filename);
    binFilename += "_bin";

    std::string humanReadableFilename(filename);
    humanReadableFilename += "_humanreadable";

    InputFileCreator ifCreator(baseX, baseY, number);
    ifCreator.printMinerals();
    ifCreator.writeToFile(binFilename, BINARY);
    ifCreator.writeToFile(humanReadableFilename, HUMAN_READABLE);
    return 0;
}

