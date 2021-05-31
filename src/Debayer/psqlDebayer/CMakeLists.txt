# CMakeList.txt : CMake project for md5, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
include_directories (${CMAKE_CURRENT_SOURCE_DIR})

file (GLOB SOURCES *.h *.cpp )
find_package(Threads REQUIRED)
add_library (psqlDebayer SHARED "psqlDebayer.h" "psqlDebayer.cpp")

find_package(libpqxx CONFIG REQUIRED)
target_link_libraries(psqlDebayer PRIVATE libpqxx::pqxx)
target_link_libraries (psqlDebayer PRIVATE pthread pq)
