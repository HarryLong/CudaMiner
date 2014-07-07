#include "gpuminer.h"

#include <iostream>
#include <math.h>
#include <cuda_runtime.h>
#include <stdio.h>

#define BLOCKSIZE 16

#define CUDA_SAFE_CALL( value , errorMsg)                                 \
{                                                                         \
  cudaError_t cudaStat = value;                                           \
  if (cudaStat != cudaSuccess)                                            \
  {                                                                       \
    std::cerr << "ERROR at line " << __LINE__ << " in file " << __FILE__  \
    << ": " << errorMsg << " | " << cudaGetErrorString(cudaStat) <<       \
    std::endl;                                                            \
    exit(EXIT_FAILURE);                                                   \
  }                                                                       \
  cudaCheckError(__LINE__);\
}\

__global__ void gpuBinning ( float *mineralData, float *resultingGrid, float stepSize, int gridLength, int gridWidth)
{
    int globalThreadIdx((blockIdx.x * blockDim.x) + threadIdx.x);

    int mineralIndex(globalThreadIdx * 3); // Each thread deals with a single mineral (3 floats)

    float x = mineralData[mineralIndex];
    float y = mineralData[mineralIndex+1];
    float value = mineralData[mineralIndex+2];

    int closestXStop = lroundf(x/stepSize);
    int closestYStop = lroundf(y/stepSize);

    float xDifference = fabs(x-(closestXStop*stepSize));
    float yDifference = fabs(y-(closestYStop*stepSize));

    bool reachable(sqrt(pow(xDifference,2)+pow(yDifference,2)) < stepSize); // Make sure it is reachable by the drone

    if(reachable)
    {
        resultingGrid[(globalThreadIdx*gridLength*gridWidth) + ((gridLength * closestYStop) + closestXStop)] = value;
    }

    __syncthreads();
}

__global__ void reduceGrid(float* gridData, int gridSize, int nGrids)
{    
    int tIdx((blockIdx.x * blockDim.x) + threadIdx.x);

    for(; nGrids > 1 ; nGrids /= 2)
    {
        if(tIdx < (nGrids/2 * gridSize))
        {
            gridData[tIdx] += gridData[tIdx + ((nGrids/2)*gridSize)];
        }
    }
    __syncthreads();
}

GPUMiner::GPUMiner(MiningData * miningData, float stepSize) : Miner(miningData, stepSize)
{

}

GPUMiner::~GPUMiner()
{

}

void GPUMiner::printDeviceInfo()
{
    int deviceCount;
    CUDA_SAFE_CALL( cudaGetDeviceCount(&deviceCount) , "Failed to get device count cusing cudaGetDeviceCount");
    std::cout << "Auto detecting gpu setup..." << std::endl;
    std::cout << "Device count: " << deviceCount << std::endl;

    int currentDevice;
    CUDA_SAFE_CALL( cudaGetDevice(&currentDevice), "Failed to get device using cudaGetDevice" );

    cudaDeviceProp deviceProp;
    {
        CUDA_SAFE_CALL( cudaGetDeviceProperties(&deviceProp, currentDevice), "Failed to get device properties using cudaGetDeviceProperties" );
    }
    std::cout << "Maximum threads per block: " << deviceProp.maxThreadsPerBlock << std::endl;
}

void GPUMiner::performBinning()
{
    /**
      TODO:
        * Iteration 1 - All data is copied to global memory [all mineral data + resulting grid]
        * Iteration 2 - Mineral data for a given block is copied into shared memory
        MISC
        * Check whether the vectors can be copied across straight
        * Use memset to zero-ify remaining data on the GPU
     * @brief CUDA_SAFE_CALL
     */
    CUDA_SAFE_CALL( cudaSetDevice( 0 ), "Unable to set device to use (method cudaSetDevice)" );

    // Calculate the required number of blocks and grids
    int nBlocks = ceil(((float)miningData->nMinerals)/((float)(BLOCKSIZE*BLOCKSIZE))); // each thread deals with binning a single mineral
    dim3 dimblock(BLOCKSIZE*BLOCKSIZE);
    dim3 dimGrid(nBlocks);
    int nThreads(nBlocks*BLOCKSIZE*BLOCKSIZE);

    std::cout << "Block dimensions: [" << dimblock.x << "," << dimblock.y << "," << dimblock.z << "]" << std::endl;
    std::cout << "Grid dimensions: [" << dimGrid.x << "," << dimGrid.y << "," << dimGrid.z << "]" << std::endl;

    // Calculate the grid size
    int miningGrid_length(ceil(miningData->baseX/stepSize)+1); // +1 for points x = 0
    int miningGrid_width(ceil(miningData->baseY/stepSize)+1); // +1 for points y = 0
    int miningGrid_noBytes(miningGrid_length*miningGrid_width*sizeof(float));
    int miningGrid_count(nThreads); // One grid for each thread

    // Allocate the memory on the device
    float* dMineralData;
    int mineralData_noBytes(miningData->nMinerals*3*sizeof(float));
    int dMineralData_noBytes(nBlocks*BLOCKSIZE*BLOCKSIZE*3*sizeof(float)); // Fill the blocks
    float* dGridData;

    std::cout << "Single grid size: " << miningGrid_noBytes << " bytes" << std::endl;
    std::cout << "Total grid size: " << miningGrid_noBytes*miningGrid_count << " bytes" << std::endl;

    // Mineral data
    {
        CUDA_SAFE_CALL( cudaMalloc( &dMineralData, dMineralData_noBytes ), "Failed to allocate device memory for dMineralData");
        CUDA_SAFE_CALL( cudaMemset( (dMineralData), 0, dMineralData_noBytes), "Failed to memset to 0 the mineral data");
    }

    // Grid data
    {
        CUDA_SAFE_CALL( cudaMalloc( &dGridData, miningGrid_noBytes*miningGrid_count ), "Failed to allocate device memory for dGridData");
        CUDA_SAFE_CALL( cudaMemset ( dGridData, 0, miningGrid_noBytes*miningGrid_count), "Failed to memset to 0 the mineral data");
    }

    // Copy the data across
    {
        CUDA_SAFE_CALL( cudaMemcpy( dMineralData, miningData->data , mineralData_noBytes, cudaMemcpyHostToDevice ), "Failed to copy rawMineralData to device");
    }

    // Run the kernel
    {
        gpuBinning <<< dimGrid, dimblock >>>(dMineralData, dGridData, stepSize, miningGrid_length, miningGrid_width);
    }

    nBlocks = ceil((miningGrid_length*miningGrid_width*miningGrid_count)/(2*BLOCKSIZE*BLOCKSIZE));
    dimGrid.x = nBlocks;
    std::cout << "Number of blocks for reduction: " << nBlocks << std::endl;

    // Reduce the resulting grid
    {
        reduceGrid<<< dimGrid, dimblock >>>(dGridData, miningGrid_length*miningGrid_width, miningGrid_count);
    }

    // Copy the data from the device
    {
//        float* tmpHMiningData = (float*) malloc(miningGrid_noBytes*miningGrid_count);
//        CUDA_SAFE_CALL(cudaMemcpy( tmpHMiningData, dGridData, miningGrid_noBytes*miningGrid_count, cudaMemcpyDeviceToHost ), "Failed to copy rawMineralData to device");

//        std::string filename("/home/harry/tmp/allgrids.txt");
//        for(int i = 0; i < nThreads; i++)
//        {
//            memcpy(grid.data, tmpHMiningData+(i*miningGrid_length*miningGrid_width), miningGrid_noBytes);
//            grid.writeToFile(filename);
//        }
        CUDA_SAFE_CALL(cudaMemcpy( grid.data, dGridData , miningGrid_noBytes, cudaMemcpyDeviceToHost), "Failed to copy grid data back to host!");
    }
}

void GPUMiner::cudaCheckError(int lineNumber)
{
    cudaError_t result = cudaGetLastError();                                                                                                                                         \
    if ( result != cudaSuccess )                                                                                                                                       \
    {
      std::cerr << "CUDA ERROR in file " << __FILE__ << " line " << lineNumber << ": " << result << std::endl;
      exit ( EXIT_FAILURE );
    }
}
