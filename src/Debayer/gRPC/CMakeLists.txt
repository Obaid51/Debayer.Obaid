# CMakeList.txt : CMake project for RawImageProcessor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
include_directories (${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../hashAlgorithms/)

file (GLOB SOURCES *.h *.cpp )

add_library (grpcServer "gRPCServer.h" "gRPCServer.cpp" "buffer.h")
target_link_libraries (grpcServer 
    logging 
    fileStream 
    ${Boost_LIBRARIES}
    protobuf::libprotoc 
    protobuf::libprotobuf 
    protobuf::libprotobuf-lite
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    hashAlgorithms
    )
