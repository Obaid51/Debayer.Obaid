# CMakeList.txt : CMake project for RawImageProcessor, include source and define
# project specific logic here.
set (CMAKE_CXX_STANDARD 20)

cmake_minimum_required (VERSION 3.8)
# Add source to this project's executable.
add_library(RawImageProcessor SHARED "RawImageProcessor.cpp" "RawImageProcessor.h" "ImageStructs.h")
include_directories("/Debayer_deps/vcpkg_cpptruths/installed/x64-linux/include/")
include_directories("../UUID")
include_directories("../md5")
find_package(Threads REQUIRED)
target_link_libraries (RawImageProcessor pthread UUID)
# TODO: Add tests and install targets if needed.
