#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "inputfilemanager.h"

InputFileManager::InputFileManager()
{
    miningData = new MiningData();
    if(sizeof(float) != 4)
        std::cout << "!!WARNING: Machine has a float size different to 4 bytes [" << sizeof(float) << "]" << std::endl;
}

InputFileManager::~InputFileManager()
{
    delete[] miningData->data;
    delete miningData;
}

float InputFileManager::fRand(float fMin, float fMax)
{
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

MiningData* InputFileManager::getMiningData()
{
    return miningData;
}
