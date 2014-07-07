cmake_minimum_required(VERSION 2.8)
project(INPUTFILEWRITER)

SET(EXECUTABLE inputFileWriter)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
ADD_EXECUTABLE(${EXECUTABLE} "inputfilewriter" "../inputfilemanager")

