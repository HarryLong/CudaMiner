#ifndef MININGDATA_H
#define MININGDATA_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>     /* malloc, free, rand */

struct Coordinate{
    int x, y;

    Coordinate(int x, int y) : x(x), y(y)
    {
    }
};

struct MiningSummary {
    double binning, aggregation, optimalPath;
    MiningSummary() : binning(.0), aggregation(.0), optimalPath(.0) {}

    void add(MiningSummary other)
    {
        binning += other.binning;
        aggregation += other.aggregation;
        optimalPath += other.optimalPath;
    }

    void average(int runs)
    {
        binning /= runs;
        aggregation /= runs;
        optimalPath /= runs;
    }
};

struct GPUMiningSummary : MiningSummary {
  double mineralAllocation, mineralCopy, mineralFree, gridAllocation, gridMemset, gridPadding, binningKernel, accumulationKernel, gridRetrieval;

  GPUMiningSummary(): mineralAllocation(.0), mineralCopy(.0), gridAllocation(.0), gridMemset(.0), gridPadding(.0), binningKernel(.0), accumulationKernel(.0), gridRetrieval(.0) {}

  void add(GPUMiningSummary other)
  {
      MiningSummary::add((MiningSummary) other);
      mineralAllocation += other.mineralAllocation;
      mineralCopy += other.mineralCopy;
      mineralFree += other.mineralFree;
      gridAllocation += other.gridAllocation;
      gridMemset += other.gridMemset;
      gridPadding += other.gridPadding;
      binningKernel += other.binningKernel;
      accumulationKernel += other.accumulationKernel;
      gridRetrieval += other.gridRetrieval;
  }

  void average(int runs)
  {
      MiningSummary::average(runs);
      mineralAllocation /= runs;
      mineralCopy /= runs;
      mineralFree /= runs;
      gridAllocation /= runs;
      gridMemset /= runs;
      gridPadding /= runs;
      binningKernel /= runs;
      accumulationKernel /= runs;
      gridRetrieval /= runs;
  }
};

struct SummaryData{
    int gridLength, nMinerals;
    bool equal;
    MiningSummary cpuSummary;
    GPUMiningSummary gpuSummary;

    SummaryData() : gridLength(0), nMinerals(0), equal(true){}
};

struct Path{
  Coordinate* path;
  int pathLength;  

  void print(float& stepsize)
  {
    for(int i = pathLength-1; i >= 0; i++)
    {
        std::cout << "[" << path[i].x*stepsize << "," << path[i].y*stepsize << "]" << std::endl;
    }
  }

  void writeToFile(std::string filename, float& stepsize)
  {
      std::ofstream file;
      file.open(filename.c_str(), std::fstream::out|std::fstream::app);
      if(file.is_open())
      {
          for(int i = pathLength; i >= 0; i--)
          {
              file << "[" << (path[i].x-1)*stepsize << "," << (path[i].y-1)*stepsize << "]" << std::endl;
          }
      }
      file.close();
  }

  bool equals(const Path& otherPath)
  {
      if(otherPath.pathLength != pathLength)
      {
          std::cout << "Path length not equal" << std::endl;
          return false;
      }

      for(int i = 0; i < pathLength; i++)
      {
          if(path[i].x != otherPath.path[i].x || path[i].y != otherPath.path[i].y)
          {
              std::cout << "Path index " << i << " not equal" << std::endl;
              return false;
          }
      }
      return true;
  }
};

struct Grid{
    int length,width,size;
    float* data; // [length][width]

    Grid() : length(0), width(0){}

    int getPathLength(){ return (length-2+width-2); } // -1 as we start from point [0,0] therefore removing a step in each dimension

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
        file.close();
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
    int nMinerals, size;
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
