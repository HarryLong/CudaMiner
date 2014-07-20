#ifndef MINER_H
#define MINER_H

#include "miningdata.h"

#include <string.h>

#define DEBUG_MSG std::cout << "Got to here --> File: " << __FILE__ << " | Function: " << __FUNCTION__ << " | Line: " << __LINE__ << std::endl;

class Miner{
public:
    Miner(MiningData * miningData, float stepSize);
    virtual ~Miner();
    virtual Grid& getGrid() {return grid;}
    virtual Path& getOptimalPath() { return optimalPath;}
    virtual void initializeGrid();
    void calculateBestPath();

    virtual void performBinning() = 0;
    virtual void createAccumulatedGrid() = 0;

protected:
    Grid grid;
    MiningData * miningData;
    Path optimalPath;
    float stepSize;
    std::vector<Path> permutations;
};

#endif
