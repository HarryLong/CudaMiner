#ifndef CPU_MINER_H
#define CPU_MINER_H

#define DEBUG_MSG std::cout << "Got to here --> File: " << __FILE__ << " | Function: " << __FUNCTION__ << " | Line: " << __LINE__ << std::endl;

#include "../common/miningdata.h"

class CPUMiner{
public:
    CPUMiner(MiningData miningData, float stepSize);
    ~CPUMiner();
    void mine();
    void performBinning();
    Path findBestPath(float& value);

protected:
    void generatePermutations();
    void permute(char* permutation, int usedX, int usedY, std::vector<Path>& allPermutations);
    void initializeGrid();

private:
    MiningData miningData;
    Grid grid;
    float stepSize;
    std::vector<Path> permutations;
};

#endif //CPU_MINER_H
