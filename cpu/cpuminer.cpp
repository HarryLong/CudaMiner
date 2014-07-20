#include "cpuminer.h"
#include "../common/timer.h"

#include <iostream>
#include <stdio.h>
#include <cmath>

CPUMiner::CPUMiner(MiningData * miningData, float stepSize) : Miner(miningData, stepSize), summary()
{
    memset(grid.data, 0, grid.size); // set the grid to '0'
}

CPUMiner::~CPUMiner()
{

}

void CPUMiner::performBinning()
{
    Timer timer;
    timer.start();
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
        bool reachable(sqrt(pow(xDifference,2)+pow(yDifference,2)) < stepSize/2.f);

        if(reachable) // Make sure it is reachable by the drone
        {
            grid.data[(closestYStop+1)*grid.length+closestXStop+1] += value;
        }
    }

    timer.stop(summary.binning);
}

void CPUMiner::createAccumulatedGrid()
{
    Timer timer;
    timer.start();

    int halfPointLayer(grid.length-2);
    for(int layer = 0; layer <= grid.getPathLength(); layer++)
    {
        int offset(max(0,layer-halfPointLayer));
        for(int layerPoint = 0; layerPoint <= (layer-2*offset) ; layerPoint++)
        {
            int x(layerPoint+offset);
            int y(layer-layerPoint-offset);

            int flatIndex(((y+1)*grid.length)+x+1); // +1 for the padding
            int leftIndex(flatIndex-1);
            int upIndex(flatIndex-grid.length);

            grid.data[flatIndex] += fmax(grid.data[leftIndex], grid.data[upIndex]);
        }
    }

    timer.stop(summary.aggregation);
}

int CPUMiner::max(const int& a, const int& b)
{
    return (a > b ? a : b);
}

MiningSummary CPUMiner::getRunSummary()
{
    return summary;
}

