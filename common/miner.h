#ifndef MINER_H
#define MINER_H

#include "miningdata.h"

#include <cmath>
#include <string.h>

#define DEBUG_MSG std::cout << "Got to here --> File: " << __FILE__ << " | Function: " << __FUNCTION__ << " | Line: " << __LINE__ << std::endl;

class Miner{
public:
    Miner(MiningData * miningData, float stepSize);
    virtual ~Miner();
    virtual Grid getGrid() {return grid;}
    virtual void performBinning() = 0;
    virtual Path findBestPath(float& value) = 0;
    virtual void initializeGrid();

protected:
    MiningData* miningData;
    Grid grid;
    float stepSize;
    std::vector<Path> permutations;
};

#endif
