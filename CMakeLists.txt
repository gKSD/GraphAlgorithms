cmake_minimum_required(VERSION 3.5)
project(BranchAndEdges)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Graph.cpp Graph.h BranchAndEdges.cpp BranchAndEdges.h DijkstraAlgorithm.cpp DijkstraAlgorithm.h)
add_executable(BranchAndEdges ${SOURCE_FILES})