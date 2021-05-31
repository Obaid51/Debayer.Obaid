# CMakeList.txt : CMake project for RawImageProcessor, include source and define
# project specific logic here.
#
project(UUID)
cmake_minimum_required (VERSION 3.8)
# Add source to this project's executable.
set(CMAKE_C_FLAGS -fPIC)
set(CMAKE_CXX_FLAGS -fPIC)
include_directories("~/vcpkg_cpptruths/installed/x64-linux/include/")
find_package(Threads REQUIRED)
#find_package(Boost COMPONENTS boost-uuid)
add_library(UUID SHARED "UUID.cpp" "UUID.h")
#target_include_directories(UUID boost-uuid_INCLUDE_DIRS)
target_link_libraries (UUID pthread psqlDebayer)

# TODO: Add tests and install targets if needed.
