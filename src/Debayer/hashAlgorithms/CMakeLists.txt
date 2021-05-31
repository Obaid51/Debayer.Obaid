# CMakeList.txt : CMake project for md5, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
include_directories (${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory ("md5")
add_subdirectory ("sha")
file (GLOB SOURCES *.h *.cpp )

add_library (hashAlgorithms "hashAlgorithms.h" "hashAlgorithms.cpp")
target_link_libraries(hashAlgorithms md5 sha)
