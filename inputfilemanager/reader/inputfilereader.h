#ifndef INPUTFILEREADER_H
#define INPUTFILEREADER_H

#include <string>
#include <fstream>

#include "../inputfilemanager.h"

class InputFileReader : public InputFileManager
{
public:
    InputFileReader(std::string filename);

private:
    float readFloat(std::ifstream& file);
};

#endif // INPUTFILEREADER_H
