# CMakeList.txt : CMake project for md5, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
include_directories (${CMAKE_CURRENT_SOURCE_DIR})

file (GLOB SOURCES *.h *.cpp )

add_library (md5 "md5.h" "md5.cpp")
