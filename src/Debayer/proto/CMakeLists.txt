# CMakeList.txt : CMake project for RawImageProcessor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
include_directories (${CMAKE_CURRENT_SOURCE_DIR})

file (GLOB SOURCES *.h *.cpp *.cc *.proto)

add_library (fileStream 
    "FileStream.grpc.pb.h" 
    "FileStream.grpc.pb.cc" 
    "FileStream.pb.h" 
    "FileStream.pb.cc")

target_link_libraries (fileStream 
    logging 
    ${Boost_LIBRARIES} 
    protobuf::libprotoc 
    protobuf::libprotobuf 
    protobuf::libprotobuf-lite
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
