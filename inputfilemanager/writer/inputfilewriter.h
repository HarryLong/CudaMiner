#ifndef INPUT_FILE_CREATOR_H
#define INPUT_FILE_CREATOR_H

#include <fstream>
#include <string>
#include <vector>

#include "../inputfilemanager.h"

class InputFileWriter : public InputFileManager {
public:
    InputFileWriter(float baseX, float baseY, int numberOfMinerals, bool optimalPathEnabled);

    void writeToFile(std::string filename, FILE_TYPE fileType);
    static void printUsage();

protected:

private:
    void writeFloat(std::ofstream& file, float& value);
};

#endif //INPUT_FILE_CREATOR_H
