cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE(CUDA REQUIRED)

#SET(CUDA_NVCC_FLAGS "--compiler-bindir /usr/lib/nvidia-cuda-toolkit/bin/")

CUDA_ADD_LIBRARY(${CUDA_LIB_NAME} "gpuminer.cu" "gpuminer.h" "../common/miner" "../common/timer" "cudaHeader")
