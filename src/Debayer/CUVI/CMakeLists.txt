# CMakeList.txt : CMake project for RawImageProcessor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/include/")

file (GLOB SOURCES *.h *.cpp )
# Add source to this project's executable.
add_library (CUVI "CuviPipeline.h" "CuviPipeline.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/cuvi.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/cuvial.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cuvico.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/cuviCore.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/cuvicv.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cuvide.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/cuviDefs.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/cuvidm.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cuvigt.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/cuviif.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/cuviio.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cuviis.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/cuviit.hpp")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/")
target_link_libraries (CUVI
    cuvi_162,
    opencv_core,
    opencv_highgui,
    opencv_imgcodecs,
    opencv_imgproc
    )

# TODO: Add tests and install targets if needed.


