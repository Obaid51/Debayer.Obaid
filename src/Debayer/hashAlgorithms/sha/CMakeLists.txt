# CMakeList.txt : CMake project for md5, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
include_directories (${CMAKE_CURRENT_SOURCE_DIR})
file (GLOB SOURCES *.h *.cpp )

add_library (sha "sha.h" "sha1.cpp" "sha224.cpp" "sha256.cpp" "sha384.cpp" "sha512.cpp")

