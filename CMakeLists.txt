cmake_minimum_required(VERSION 2.8)
project(ASTROMINER)

FIND_PACKAGE(CUDA REQUIRED)

SET(CUDA_LIB_NAME "cuda")
SET(CPU_LIB_NAME "cpu")
SET(INPUT_READER_LIB_NAME "inputfilereader")
SET(LIBS ${CUDA_LIB_NAME} ${CPU_LIB_NAME} ${INPUT_READER_LIB_NAME})
SET(EXECUTABLE "AstroMiner")
SET(CUDA_NVCC_FLAGS "--gpu-architecture=sm_30")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #DEBUG

add_subdirectory(cpu)
add_subdirectory(cuda)
add_subdirectory(inputfilemanager)

CUDA_ADD_EXECUTABLE(${EXECUTABLE} "AstroMiner.cpp")
ADD_DEPENDENCIES(${EXECUTABLE} ${LIBS})
TARGET_LINK_LIBRARIES(${EXECUTABLE} ${LIBS})

