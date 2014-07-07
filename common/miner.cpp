#include "miner.h"
#include <stdlib.h>     /* malloc, free, rand */

Miner::Miner(MiningData* miningData, float stepSize) : miningData(miningData), stepSize(stepSize), permutations()
{
    initializeGrid();
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

void Miner::initializeGrid()
{
    // Calculate the grid size
    grid.length = ceil(miningData->baseX/stepSize)+1; // +1 for points x = 0
    grid.width = ceil(miningData->baseY/stepSize)+1; // +1 for points y = 0

    grid.data = (float*) malloc(grid.length*grid.width*sizeof(float));
}
