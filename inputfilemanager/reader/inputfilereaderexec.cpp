#include <iostream>

#include "inputfilereader.h"

#define ARG_INPUTFILE "-inputfile"

void printUsage()
{
  std::cout << "Usage: ./inputfilereader -inputfile <filename>" << std::endl;
}

int main(int argc, char *argv[])
{
    char * filename = NULL;
    int argIdx(1);
    while(argIdx < argc-1)
    {
      if(std::string(argv[argIdx]) == ARG_INPUTFILE)
      {
        filename = argv[argIdx+1];	  
      }
      else
      {
         printUsage();
         return 1;
      }
    }

    if(filename == NULL)
    {
        printUsage();
        return 1;
    }

    std::cout << "Reading in input file: " << filename << std::endl;
    
    InputFileReader reader;
    if(!reader.parse(filename))
    {
        std::cerr << "Unable to parse input file" << std::endl;
        return 1;
    }
    reader.getMiningData()->print();
    return 0;
}


