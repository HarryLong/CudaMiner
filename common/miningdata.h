#ifndef MININGDATA_H
#define MININGDATA_H

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

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
    float** data; // [length][width]
    int getPathLength(){ return (length-1+width-1); } // -1 as we start from point [0,0] therefore removing a step in each dimension
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
                    ss << data[x][y];
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

struct BaseStation{
    float x, y;
    BaseStation(float x, float y) : x(x), y(y) {}
    BaseStation() : x(0.f), y(0.f) {}
};

struct Mineral{
    float x, y, value;
    Mineral(float x, float y, float value) : x(x), y(y), value(value) {}
};

struct MiningData{
    BaseStation base;
    std::vector<Mineral> minerals;
};

#endif //MININGDATA_H
