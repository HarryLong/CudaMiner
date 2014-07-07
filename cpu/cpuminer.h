#ifndef CPU_MINER_H
#define CPU_MINER_H

#include "../common/miner.h"

class CPUMiner : public Miner{
public:
    CPUMiner(MiningData * miningData, float stepSize);
    virtual ~CPUMiner();
    virtual void performBinning();
    virtual Path findBestPath(float& value);
    virtual void initializeGrid();

protected:
    void generatePermutations();
    void permute(char* permutation, int usedX, int usedY, std::vector<Path>& allPermutations);

private:
};

#endif //CPU_MINER_H
