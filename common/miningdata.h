#ifndef MININGDATA_H
#define MININGDATA_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>     /* malloc, free, rand */

#define DOWN 'D' // for the path
#define RIGHT 'R' // for the path

struct Path{
  char* path;
  int pathLength;  

  Path(char* path, int pathLength) : path(path), pathLength(pathLength) {}
  void print()
  {
    for(int i = 0; i < pathLength; i++)
    {
      if(i != 0)
        std::cout << ",";
      else
        std::cout << "{";

      if(path[i] == RIGHT)
        std::cout << "RIGHT";
      else
        std::cout << "DOWN";
    }
    std::cout << "}" << std::endl;
  }
};

struct Grid{
    int length,width;
    float* data; // [length][width]

    Grid() : length(0), width(0){}

    int getPathLength(){ return (length-1+width-1); } // -1 as we start from point [0,0] therefore removing a step in each dimension

    float get(int x, int y)
    {
        return data[y*length+x];
    }

    void set(int x, int y, float value)
    {
       data[y*length+x] = value;
    }

    void writeToFile(std::string filename)
    {
        std::ofstream file;
        file.open(filename.c_str(), std::fstream::out|std::fstream::app);
        if(file.is_open())
        {
            for(int x = 0; x < length; x++)
            {
                if(x == 0)
                    file << "|";
                file << "------|";
            }
            file << std::endl;
            for(int y = 0; y < width; y++)
            {
                for(int x = 0; x < length; x++)
                {
                    if(x == 0)
                        file << "|";
                    std::stringstream ss (std::stringstream::in | std::stringstream::out);
                    ss << get(x,y);
                    std::string value(ss.str());
                    value.resize(6,' ');
                    file << value << "|";
                }
                file << std::endl;
                for(int x = 0; x < length; x++)
                {
                    if(x == 0)
                        file << "|";
                    file << "      |";
                }
                file << std::endl;
                for(int x = 0; x < length; x++)
                {
                    if(x == 0)
                        file << "|";
                    file << "------|";
                }
                file << std::endl;
            }
        }
        else
            std::cerr << "Unable to open file: " << filename << std::endl;

        file << std::endl << std::endl;
    }

    void print()
    {
        if(length < 50 && width < 50)
        {
            for(int x = 0; x < length; x++)
            {
                if(x == 0)
                    std::cout << "|";
                std::cout << "------|";
            }
            std::cout << std::endl;
            for(int y = 0; y < width; y++)
            {
                for(int x = 0; x < length; x++)
                {
                    if(x == 0)
                        std::cout << "|";
                    std::stringstream ss (std::stringstream::in | std::stringstream::out);
                    ss << get(x,y);
                    std::string value(ss.str());
                    value.resize(6,' ');
                    std:: cout << value << "|";
                }
                std::cout << std::endl;
                for(int x = 0; x < length; x++)
                {
                    if(x == 0)
                        std::cout << "|";
                    std::cout << "      |";
                }
                std::cout << std::endl;
                for(int x = 0; x < length; x++)
                {
                    if(x == 0)
                        std::cout << "|";
                    std::cout << "------|";
                }
                std::cout << std::endl;
            }
        }
        else
        {
            std::cout << "!GRID TOO LARGE!" << std::endl;
        }
    }
};

struct Mineral{
    float x, y, value;
};

struct MiningData{
    float baseX, baseY;
    int nMinerals;
    float* data;

    MiningData(): baseX(0), baseY(0), nMinerals(0) {}

    void print()
    {
        std::cout << "Base Station: [" << baseX << "," << baseY << "]" << std::endl;
        std::cout << "********MINERALS********" << std::endl;
        for(int i = 0; i < nMinerals; i++)
        {
            std::cout << "[X: " << data[i*3] << ", Y:" << data[i*3+1] << "] --> " << data[i*3+2] << std::endl;
        }
        std::cout << "************************" << std::endl;
    }
};

#endif //MININGDATA_H
