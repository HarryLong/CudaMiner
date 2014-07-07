#ifndef INPUT_FILE_MANAGER_H
#define INPUT_FILE_MANAGER_H

#include <vector>
#include <ostream>
#include "../common/miningdata.h"

#define DEBUG_MSG std::cout << "Got to here --> File: " << __FILE__ << " | Function: " << __FUNCTION__ << " | Line: " << __LINE__ << std::endl;

class InputFileManager{
public:
    InputFileManager();
    virtual ~InputFileManager();

    static float fRand(float fMax) {return fRand(0.f, fMax); }
    static float fRand(float fMin, float fMax);
    MiningData* getMiningData();

protected:
     MiningData * miningData;

private:
};

#endif //INPUT_FILE_MANAGER_H
