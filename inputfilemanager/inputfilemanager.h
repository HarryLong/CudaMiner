#ifndef INPUT_FILE_MANAGER_H
#define INPUT_FILE_MANAGER_H

#include <vector>
#include <ostream>
#include "../common/miningdata.h"

enum FILE_TYPE{
    HUMAN_READABLE,
    BINARY
};

class InputFileManager{
public:
    InputFileManager();
    InputFileManager(float baseX, float baseY);

    static float fRand(float fMax) {return fRand(0.f, fMax); }
    static float fRand(float fMin, float fMax);
    MiningData getMiningData();

    // Test methods
    void printMinerals();

protected:
     MiningData miningData;

private:
};

#endif //INPUT_FILE_MANAGER_H
