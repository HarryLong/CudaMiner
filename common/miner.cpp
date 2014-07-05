#include "miner.h"

Miner::Miner(MiningData miningData, float stepSize) : miningData(miningData), stepSize(stepSize), permutations()
{
}

Miner::~Miner()
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

void Miner::initializeGrid()
{
    // Calculate the grid size
    grid.length = ceil(miningData.base.x/stepSize)+1; // +1 for points x = 0
    grid.width = ceil(miningData.base.y/stepSize)+1; // +1 for points y = 0

    grid.data = new float*[grid.length];

    for(int x = 0; x < grid.length; ++x)
    {
        grid.data[x] = new float[grid.width];
        memset(grid.data[x],0, grid.width*sizeof(float));
    }
}
