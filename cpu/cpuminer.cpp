#include "cpuminer.h"

#include <string.h>
#include <iostream>
#include <cmath>

CPUMiner::CPUMiner(MiningData miningData, float stepSize) : miningData(miningData), stepSize(stepSize)
{
}

CPUMiner::~CPUMiner()
{
    // Delete grid data
    for(int i = 0; i < grid.length; ++i)
    {
        delete[] grid.data[i];
    }
    delete[] grid.data;

    // Delete permutations
    for(int i = 0; i < permutations.size(); ++i)
    {
        delete[] permutations[i].path;
    }
}

void CPUMiner::initializeGrid()
{
    // Calculate the grid size
    grid.length = ceil(miningData.base.x/stepSize);
    grid.width = ceil(miningData.base.y/stepSize);

    grid.data = new float*[grid.width];
    for(int i = 0; i < grid.width; ++i)
    {
        grid.data[i] = new float[grid.length];
    }
}

void CPUMiner::performBinning()
{
    for(std::vector<Mineral>::iterator it = miningData.minerals.begin(); it != miningData.minerals.end(); it++)
    {
        int xIndex = round(it->x/stepSize);
        int yIndex = round(it->y/stepSize);
        grid.data[xIndex][yIndex] += it->value;
    }
}

Path CPUMiner::findBestPath(float& value)
{
    // Initialize the grid
    std::cout << "Initializing grid...";
    initializeGrid();
    std::cout << "OK!" << std::endl;

    // Fill the frid with mineral data
    std::cout << "Filling grid with mineral data provided...";
    performBinning();
    std::cout << "OK!" << std::endl;

    // Generate all possible permutations
    std::cout << "Generating all possible grid permutations (Grid size: [" << grid.length << "," << grid.width << "]) ...";
    generatePermutations();
    std::cout << "OK! (" << permutations.size() << " permutations generated)" << std::endl;

    // Iterate through all possible paths and remember the best
    std::cout << "Finding most optimal path...";
    int bestPathIdx = 0;
    float bestPathValue(-1.f);

    for(int i = 0; i < permutations.size(); i++)
    {
        char* path = permutations[i].path;
        int x(0),y(0);
        float pathValue(grid.data[x][y]); // It will always take the minerals from its current position
        std::cout << "Following path: ";
        permutations[i].print();
        std::cout << std::endl;
        for(int i = 0; i < grid.length+grid.width; i++)
        {
            if(path[i] == RIGHT)
            {
                std::cout << "GOING RIGHT" << std::endl;
                x++;
            }
            else
            {
                std::cout << "GOING DOWN" << std::endl;
                y++;
            }
            pathValue += grid.data[x][y];
        }
        if(pathValue > bestPathValue)
        {
            bestPathIdx = i;
            bestPathValue = pathValue;
        }
    }
    std::cout << "OK!" << std::endl;

    value = bestPathValue;
    return permutations[bestPathIdx];
}

void CPUMiner::generatePermutations()
{
    char * startRight = new char[grid.getPathLength()];
    startRight[0] = RIGHT;

    char * startDown = new char[grid.getPathLength()];
    startDown[0] = DOWN;

    permute(startRight,1,0,permutations);
    permute(startDown,0,1,permutations);
}

void CPUMiner::permute(char* permutation, int usedRight, int usedDown, std::vector<Path>& allPermutations)
{
    if(usedRight+usedDown == grid.getPathLength()) // i.e
        allPermutations.push_back(Path(permutation,grid.getPathLength()));

    if(usedRight < grid.length-1)
    {
        char* newPermutation = new char[grid.getPathLength()];
        memcpy(newPermutation, permutation,grid.getPathLength());
        newPermutation[usedRight+usedDown] = RIGHT;
        permute(newPermutation, usedRight+1, usedDown, allPermutations);
    }
    if(usedDown < grid.width-1)
    {
        permutation[usedRight+usedDown] = 'y';
        permute(permutation, usedRight, usedDown+1, allPermutations);
    }
}
