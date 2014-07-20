#include "gpuminer.h"

#include <iostream>
#include <stdio.h>
#include "cudaHeader.h"
#include "../common/timer.h"

#define BLOCKSIZE 16

//__global__ void gpuBinning_01 ( float *mineralData, float *resultingGrid, float stepSize, int gridLength)
//{
//    int globalThreadIdx((blockIdx.x * blockDim.x) + threadIdx.x);

//    int mineralIndex(globalThreadIdx * 3); // Each thread deals with a single mineral (3 floats)

//    float x = mineralData[mineralIndex];
//    float y = mineralData[mineralIndex+1];
//    float value = mineralData[mineralIndex+2];

//    int closestXStop = lroundf(x/stepSize);
//    int closestYStop = lroundf(y/stepSize);

//    float xDifference = fabs(x-(closestXStop*stepSize));
//    float yDifference = fabs(y-(closestYStop*stepSize));

//    bool reachable(sqrt(pow(xDifference,2)+pow(yDifference,2)) < stepSize); // Make sure it is reachable by the drone

//    if(reachable)
//    {
//        resultingGrid[(globalThreadIdx*gridLength*gridLength) + ((gridLength * closestYStop) + closestXStop)] = value;
//    }

//    __syncthreads();
//}

//__global__ void reduceGrid(float* gridData, int gridSize, int nGrids)
//{
//    int tIdx((blockIdx.x * blockDim.x) + threadIdx.x);

//    for(; nGrids > 1 ; nGrids /= 2)
//    {
//        if(tIdx < (nGrids/2 * gridSize))
//        {
//            gridData[tIdx] += gridData[tIdx + ((nGrids/2)*gridSize)];
//        }
//    }
//    __syncthreads();
//}

__global__ void gpuBinning_02 ( float *mineralData, float *resultingGrid, float stepSize, int gridLength, int nMinerals)
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

    bool reachable(sqrt(pow(xDifference,2)+pow(yDifference,2)) < stepSize/2.f); // Make sure it is reachable by the drone

    if(reachable && globalThreadIdx < nMinerals)
    {
        atomicAdd(&resultingGrid[gridLength * (closestYStop+1) + closestXStop+1], value); // +1 for the padding
    }
}

// TODO: You can drop the accumulatedGrid as data can be overwritten
__global__ void gpuCreateAccumulatedGrid(float* grid, int gridLength, int layer)
{
    int halfPointLayer(gridLength-2); // -2 as there is left-side padding
    int offset(max(0,layer - halfPointLayer)); // Used to deal with the diagonal getting smaller

    int globalThreadIdx((blockIdx.x * blockDim.x) + threadIdx.x);

    if(globalThreadIdx <= layer-(2*offset))
    {
        int x(globalThreadIdx + offset);
        int y(layer-globalThreadIdx-offset);

        int flatIndex(((y+1)*gridLength)+x+1); // +1 for the padding
        int leftIndex(flatIndex-1);
        int upIndex(flatIndex-gridLength);

        grid[flatIndex] += max(grid[leftIndex],grid[upIndex]);
    }
}

GPUMiner::GPUMiner(MiningData * miningData, float stepSize) : Miner(miningData, stepSize), dimblock(BLOCKSIZE*BLOCKSIZE), summary()
{
}

GPUMiner::~GPUMiner()
{
    CUDA_SAFE_CALL( cudaFree(dGridData), "Failed to free device grid data");
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
    Timer timer;

    CUDA_SAFE_CALL( cudaSetDevice( 0 ), "Unable to set device to use (method cudaSetDevice)" );

    // Calculate the required number of blocks and grids
    int nBlocks = ceil(((float)miningData->nMinerals)/((float)(BLOCKSIZE*BLOCKSIZE))); // each thread deals with binning a single mineral
    dim3 dimGrid(nBlocks);

    // MINERAL DATA
    float* dMineralData;
    {
        timer.start();
        CUDA_SAFE_CALL( cudaMalloc( &dMineralData, miningData->size ), "Failed to allocate device memory for dMineralData");
        cudaDeviceSynchronize();
        timer.stop(summary.mineralAllocation);

        timer.start();
        CUDA_SAFE_CALL( cudaMemcpy( dMineralData, miningData->data , miningData->size, cudaMemcpyHostToDevice ), "Failed to copy rawMineralData to device");
        cudaDeviceSynchronize();
        timer.stop(summary.mineralCopy);
    }

    // GRID DATA
    {
        // Allocate memory
        timer.start();
        CUDA_SAFE_CALL( cudaMalloc( &dGridData, grid.size), "Failed to allocate device memory for dGridData");
        cudaDeviceSynchronize();
        timer.stop(summary.gridAllocation);

        timer.start();
        CUDA_SAFE_CALL( cudaMemset ( &dGridData[grid.length], 0, grid.size-(grid.length*sizeof(float))), "Failed to memset to 0 the mineral data");
        cudaDeviceSynchronize();
        timer.stop(summary.gridMemset);

        // Grid Padding
        timer.start();
        CUDA_SAFE_CALL( cudaMemset ( dGridData, 0xbf, grid.length*sizeof(float)), "Failed to memset to the grid data");
        for(int i = 1; i < grid.width; i++)
        {
            CUDA_SAFE_CALL( cudaMemset ( &dGridData[grid.length*i], 0xbf, sizeof(float)), "Failed to memset to the grid data");
        }
        cudaDeviceSynchronize();
        timer.stop(summary.gridPadding);
    }


    // Run the kernel
    {
        timer.start();
        gpuBinning_02<<< dimGrid, dimblock>>>(dMineralData, dGridData, stepSize, grid.length, miningData->nMinerals);
        cudaDeviceSynchronize();
        timer.stop(summary.binningKernel);
    }
    // Free the mining data as it is no longer needed
    {
        timer.start();
        CUDA_SAFE_CALL( cudaFree(dMineralData), "Failed to free device mineral data");
        cudaDeviceSynchronize();
        timer.stop(summary.mineralFree);
    }
    summary.binning = summary.mineralAllocation + summary.mineralCopy + summary.gridAllocation + summary.gridMemset + summary.gridPadding + summary.binningKernel + summary.mineralFree;
}

void GPUMiner::createAccumulatedGrid()
{
    Timer t;

    int nBlocks = ceil(((float)grid.length)/((float)(BLOCKSIZE*BLOCKSIZE))); // The maximum number of threads will be on the diagonal
    dim3 dimGrid(nBlocks);

    {
        t.start();
        for(int i = 0; i <= grid.getPathLength(); i++)
        {
            gpuCreateAccumulatedGrid<<< dimGrid, dimblock >>>(dGridData,grid.length,i);
        }
        cudaDeviceSynchronize();
        t.stop(summary.accumulationKernel);
    }

    // Copy the data back from the device
    {
        t.start();
        CUDA_SAFE_CALL( cudaMemcpy( grid.data, dGridData , grid.size, cudaMemcpyDeviceToHost), "Failed to copy grid data from device to host");
        cudaDeviceSynchronize();
        t.stop(summary.gridRetrieval);
    }
    summary.aggregation = summary.accumulationKernel + summary.gridRetrieval;
}

GPUMiningSummary GPUMiner::getRunSummary()
{
    return summary;
}
