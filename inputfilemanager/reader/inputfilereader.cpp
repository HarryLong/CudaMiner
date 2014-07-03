#include <iostream>
#include <iostream>
#include <stdlib.h>     /* atof */

#include "inputfilereader.h"

InputFileReader::InputFileReader(std::string filename)
{
    std::ifstream file (filename.c_str(), std::fstream::in | std::fstream::binary|std::fstream::ate);
    if (file.is_open())
    {
      std::streampos size = file.tellg();
      if(size % (3*sizeof(float)) != 0)
      {
          std::cerr << "Invalid file: it doesn't contain a multiple of 3 single point floats" << std::endl;
          return;
      }

      file.seekg (0, std::fstream::beg); // 0 from the beginning

      // read the basex and basey
      float baseX = readFloat(file);
      float baseY = readFloat(file);
      miningData.base = BaseStation(baseX, baseY);
      readFloat(file); // The file then has the value for the basestation but can be ignored

      while(file.tellg() != size)
      {
          float x = readFloat(file);
          float y = readFloat(file);
          float value = readFloat(file);

          miningData.minerals.push_back(Mineral(x,y,value));
      }
    }
    else
        std::cout << "Unable to open file: " << filename;

    file.close();
}

float InputFileReader::readFloat(std::ifstream& file)
{
    float ret;
    file.read( reinterpret_cast <char*> (&ret), sizeof( float ) );
    return ret;
}

