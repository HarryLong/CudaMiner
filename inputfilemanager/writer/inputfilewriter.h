#ifndef INPUT_FILE_CREATOR_H
#define INPUT_FILE_CREATOR_H

#include <fstream>
#include <string>
#include <vector>

#include "../inputfilemanager.h"

class InputFileWriter : public InputFileManager {
public:
    InputFileWriter(float baseX, float baseY, int numberOfMinerals);

    void writeToFile(std::string filename, FILE_TYPE fileType);

protected:

private:
    void writeFloat(std::ofstream& file, float& value);
};

#endif //INPUT_FILE_CREATOR_H
