#include <iostream>
#include <iostream>
#include <stdlib.h>     /* atof */
#include <exception>

#include "inputfilereader.h"

bool InputFileReader::parse(std::string filename)
{
    std::ifstream file (filename.c_str(), std::fstream::in | std::fstream::binary|std::fstream::ate);
    if (file.is_open())
    {
      std::streampos size = file.tellg();
      if(size % (3*sizeof(float)) != 0)
      {
          std::cerr << "Invalid file: it doesn't contain a multiple of 3 single point floats" << std::endl;
          return false;
      }
      file.seekg (0, std::fstream::beg); // 0 from the beginning

      // read the basex and basey
      miningData->baseX = readFloat(file);
      miningData->baseY = readFloat(file);
      miningData->size = (size-3*sizeof(float)); // remove the 3 floats for the base station
      miningData->nMinerals =  miningData->size/(sizeof(float)*3);
      miningData->data = (float*) malloc(miningData->size);

      readFloat(file); // The file then has the value for the basestation but can be ignored as its always 0

      int i(0);
      while(file.tellg() != size)
      {
          miningData->data[i++] = readFloat(file);
      }
    }
    else
    {
        std::cout << "Unable to open file: " << filename << std::endl;
        return false;
    }
    file.close();
    return true;
}

float InputFileReader::readFloat(std::ifstream& file)
{
    float ret;
    file.read( reinterpret_cast <char*> (&ret), sizeof( float ) );
    return ret;
}

