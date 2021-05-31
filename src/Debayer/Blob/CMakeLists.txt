# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)
# Add source to this project's executable.
add_library (azureblob SHARED "azureblob.cpp" "azureblob.h" "blob.h")
#include_directories("/Debayer_deps/vcpkg_cpptruths/installed/x64-linux/include/")
#target_link_libraries(azureblob /Debayer_deps/vcpkg_cpptruths/packages/azure-storage-cpp_x64-linux/lib/libazurestorage.a)
#target_link_libraries(azureblob azurestorage)
target_link_libraries(azureblob /Debayer_deps/vcpkg_cpptruths/installed/x64-linux/lib/libazurestorage.a)
#target_include_directories(azureblob /Debayer_deps/vcpkg_cpptruths/buildtrees/azure-storage-cpp/src/v7.5.0-1d01ff61d2.clean/Microsoft.WindowsAzure.Storage/includes/)
# TODO: Add tests and install targets if needed.
