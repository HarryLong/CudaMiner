#include "cpuminer.h"

#include <iostream>

#include <stdio.h>

CPUMiner::CPUMiner(MiningData * miningData, float stepSize) : Miner(miningData, stepSize)
{
    initializeGrid();
}

CPUMiner::~CPUMiner()
{

}

void CPUMiner::performBinning()
{
    // Fill the grid with mineral data
    for(int i = 0; i < miningData->nMinerals; i++)
    {
        float x(miningData->data[i*3]);
        float y(miningData->data[i*3+1]);
        float value(miningData->data[i*3+2]);

        // First calculate the stop which is the closest to this point
        int closestXStop = round(x/stepSize);
        int closestYStop = round(y/stepSize);

        float xDifference = fabs(x-(closestXStop*stepSize));
        float yDifference = fabs(y-(closestYStop*stepSize));
        bool reachable(sqrt(pow(xDifference,2)+pow(yDifference,2)) < stepSize);

//        printf("Mineral: [%.4f,%.4f] -->  %.4f \n", x,y,value);
//        printf("Closest stop: [%d,%d]\n",closestXStop,closestYStop);
//        printf("X difference: [%.4f,%.4f]\n",xDifference,yDifference);
//        printf("Current value: %.4f\n", grid.get(closestXStop, closestYStop));
//        printf("Reachable: %d\n", reachable);
//        printf("Index: %d | Current value: %.4f\n", grid.length*closestYStop + closestXStop, grid.get(closestXStop, closestYStop));

        if(reachable) // Make sure it is reachable by the drone
        {
            grid.set(closestXStop,closestYStop,grid.get(closestXStop, closestYStop)+value);
        }
    }
}

Path CPUMiner::findBestPath(float& value)
{
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
        float pathValue(grid.get(x,y)); // It will always take the minerals from its current position
        for(int i = 0; i < grid.length+grid.width; i++)
        {
            if(path[i] == RIGHT)
            {
                x++;
            }
            else
            {
                y++;
            }
            pathValue += grid.get(x,y);
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

// Need to initialize them to zero for the CPU
void CPUMiner::initializeGrid()
{
    Miner::initializeGrid();
    std::cout << "Grid: [" << grid.length << "," << grid.width << "]" << std::endl;
    memset(grid.data, 0, grid.length*grid.width*sizeof(float));
}

