#ifndef CUDA_HEADER_H
#define CUDA_HEADER_H

// A macro to make a cuda call, printing an error message and exiting the program if an error occurs
#define CUDA_SAFE_CALL( value , errorMsg)                                 \
{                                                                         \
  cudaError_t cudaStat = value;                                           \
  if (cudaStat != cudaSuccess)                                            \
  {                                                                       \
    fprintf(stderr, "ERROR: %s [ %s at line %d in file %s ]\n",           \
        errorMsg, cudaGetErrorString(cudaStat), __LINE__, __FILE__ );     \
    exit(EXIT_FAILURE);                                                   \
  }                                                                       \
} 

// Defines for GPU Architecture types (using the SM version to determine the # of cores per SM)
typedef struct
{
    int SM; // 0xMm (hexidecimal notation), M = SM Major version, and m = SM minor version  ie 0x12 (18) is compute 1.2
    int value;
} SMVal;

#endif // CUDA_HEADER_H
