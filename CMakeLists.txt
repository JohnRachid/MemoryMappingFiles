cmake_minimum_required(VERSION 3.10)
project(MemoryMappingFiles)

set(CMAKE_CXX_STANDARD 98)

add_executable(MemoryMappingFiles prov-rep.cpp alloc.cpp alloc.h)