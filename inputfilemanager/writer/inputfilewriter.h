#ifndef INPUT_FILE_CREATOR_H
#define INPUT_FILE_CREATOR_H

#include <fstream>
#include <string>
#include <vector>

#include "../inputfilemanager.h"

class InputFileWriter : public InputFileManager {
public:
    InputFileWriter(float baseX, float baseY, int numberOfMinerals, bool optimalPathEnabled, std::string binFilename, std::string readableFilename);

    void writeToBinFile(std::ofstream& binaryfile, Mineral& mineral);
    void writeToReadableFile(std::ofstream& binaryfile, Mineral& mineral, bool base = false);
    static void printUsage();

protected:

private:
};

#endif //INPUT_FILE_CREATOR_H
