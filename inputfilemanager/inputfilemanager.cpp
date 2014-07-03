#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "inputfilemanager.h"

InputFileManager::InputFileManager()
{
    if(sizeof(float) != 4)
        std::cout << "!!WARNING: Machine has a float size different to 4 bytes [" << sizeof(float) << "]" << std::endl;
}

InputFileManager::InputFileManager(float baseX, float baseY)
{
    miningData.base = BaseStation(baseX, baseY);
    if(sizeof(float) != 4)
        std::cout << "!!WARNING: Machine has a float size different to 4 bytes [" << sizeof(float) << "]" << std::endl;
}

float InputFileManager::fRand(float fMin, float fMax)
{
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

MiningData InputFileManager::getMiningData()
{
    return miningData;
}

void InputFileManager::printMinerals()
{
    std::cout << "Base Station: [" << miningData.base.x << "," << miningData.base.y << "]" << std::endl;
    std::cout << "********MINERALS********" << std::endl;
    for(std::vector<Mineral>::iterator it = miningData.minerals.begin(); it != miningData.minerals.end(); it++)
    {
        std::cout << "[X: " << it->x << ", Y:" << it->y << "] --> " << it->value << std::endl;
    }
    std::cout << "************************" << std::endl;
}
