#ifndef GPUMINER_H
#define GPUMINER_H

#include <string>

#include "../common/miner.h"

class GPUMiner : public Miner{
public:
    GPUMiner(MiningData * miningData, float stepSize);
    virtual ~GPUMiner();
    virtual void performBinning();
    virtual Path findBestPath(float& value) {return permutations[0]; }

    // TEMPORARY METHOD
    void printDeviceInfo();

private:
    void cudaCheckError(int lineNumber);
};

#endif
