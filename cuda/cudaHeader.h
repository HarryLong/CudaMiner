#ifndef CUDA_HEADER_H
#define CUDA_HEADER_H

#include <iostream>
#include <cuda_runtime.h>
#include <stdio.h>

#define CUDA_SAFE_CALL( value , errorMsg)                           \
{                                                                         \
  cudaError_t cudaStat = value;                                           \
  if (cudaStat != cudaSuccess)                                            \
  {                                                                       \
    std::cerr << "ERROR at line " << __LINE__ << " in file " << __FILE__  \
    << ": " << errorMsg << " | " << cudaGetErrorString(cudaStat) <<       \
    std::endl;                                                            \
    exit(EXIT_FAILURE);                                                   \
  }\
}

#endif // CUDA_HEADER_H
