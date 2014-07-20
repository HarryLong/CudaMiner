#ifndef CPU_MINER_H
#define CPU_MINER_H

#include "../common/miner.h"

class CPUMiner : public Miner{
public:
    CPUMiner(MiningData * miningData, float stepSize);
    virtual ~CPUMiner();
    virtual void performBinning();
    virtual void createAccumulatedGrid();
    virtual MiningSummary getRunSummary();

protected:
    void generatePermutations();
    void permute(char* permutation, int usedX, int usedY, std::vector<Path>& allPermutations);

private:
    int max(const int& a, const int& b);
    MiningSummary summary;
};

#endif //CPU_MINER_H
