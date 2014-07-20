#ifndef GPUMINER_H
#define GPUMINER_H

#include <string>

#include "../common/miner.h"
#include <cuda_runtime.h>

class GPUMiner : public Miner{
public:
    GPUMiner(MiningData * miningData, float stepSize);
    virtual ~GPUMiner();
    virtual void performBinning();
    virtual void createAccumulatedGrid();
    virtual GPUMiningSummary getRunSummary();

    // TEMPORARY METHOD
    void printDeviceInfo();

private:
    void cudaCheckError(int lineNumber);
    float* dGridData;
    dim3 dimblock;
    GPUMiningSummary summary;
};

#endif
