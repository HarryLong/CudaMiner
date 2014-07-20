#include "miner.h"
#include <stdlib.h>     /* malloc, free, rand */
#include <math.h>

Miner::Miner(MiningData* miningData, float stepSize) : miningData(miningData), stepSize(stepSize), permutations()
{
    initializeGrid();
}

void Miner::initializeGrid()
{
    // Calculate the grid size
    grid.length = ceil(miningData->baseX/stepSize)+2; // +2 for points x = 0 and padding for optimization
    grid.width = ceil(miningData->baseY/stepSize)+2; // +2 for points y = 0 and padding for optimization
    grid.size = grid.length*grid.width*sizeof(float);

    grid.data = (float*) malloc(grid.size);
}

void Miner::calculateBestPath()
{
    int pathLength(grid.getPathLength());
    optimalPath.pathLength = pathLength;
    optimalPath.path = (Coordinate*) malloc(pathLength*sizeof(Coordinate));

    int currentX(grid.length-1);
    int currentY(grid.width-1);

    for(int i = 0; i <= pathLength; i++)
    {
        int flatIndex(currentY*grid.width+currentX);

        optimalPath.path[i]=Coordinate(currentX,currentY);

        if(currentY == 1)
            currentX--;
        else if(currentX == 1)
            currentY--;
        else if(grid.data[flatIndex-1] > grid.data[flatIndex-grid.length])
            currentX--;
        else
            currentY--;
    }
}

Miner::~Miner()
{
    // Delete grid data
    delete[] grid.data;

    // Delete permutations
    for(int i = 0; i < permutations.size(); ++i)
    {
        delete[] permutations[i].path;
    }
}
