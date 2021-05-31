cmake_minimum_required (VERSION 3.10)

set (PROJECT_NAME debayer)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_C_COMPILER "clang" CACHE STRING "" FORCE)
set (CMAKE_CXX_COMPILER "clang++" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS "-fno-limit-debug-info")

project (${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)
set (AUTO_VCPKG_GIT_TAG    2020.11-1)  
set (Boost_USE_STATIC_LIBS        ON)  # only find static libs
set (Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set (Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set (Boost_USE_MULTITHREADED      ON)
set (Boost_USE_STATIC_RUNTIME     ON)
set (-DCMAKE_TOOLCHAIN_FILE=~/vcpkg_cpptruths/scripts/buildsystems/vcpkg.cmake)
set (DEBAYER_PROJECT_DEPENDENCIES 
        boost-thread
        pthread       
        boost-log
        boost-filesystem
        boost-chrono
        boost-program-options
        boost-tti
        boost-uuid
        c-ares
        zlib
        upb
        re2
        protobuf
        grpc
        cryptopp
        openssl
        #cpprestsdk
        #azure-storage-cpp
        )

set (libpqxx_DIR /Debayer_deps/vcpkg_cpptruths/buildtrees/libpqxx/x64-linux-rel/)

if (NOT DEFINED ${CMAKE_TOOLCHAIN_FILE})
  message ("CMAKE_TOOLCHAIN_FILE is not defined")
  if (NOT DEFINED $ENV{VCPKG_ROOT})
    message ("ENV{VCPKG_ROOT} is not defined")
    set (VCPKG_ROOT $ENV{HOME}/vcpkg_cpptruths)
    set (Boost_INCLUDE_DIR ${VCPKG_ROOT}/installed/x64-linux/include)
    set (BOOST_ROOT {VCPKG_ROOT}/installed/x64-linux/include CACHE PATH "Boost library path" )
    set (CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    set (Boost_NO_SYSTEM_PATHS on CACHE BOOL "Do not search system for Boost" )
  else ()
    set (VCPKG_ROOT $ENV{VCPKG_ROOT})
  endif ()

  message ("{VCPKG_ROOT} has been set here: ${VCPKG_ROOT}")

  if (NOT EXISTS ${VCPKG_ROOT})
    message ("Cloning vcpkg in ${VCPKG_ROOT}")
    execute_process (COMMAND git clone https://github.com/Microsoft/vcpkg.git ${VCPKG_ROOT})
  else ()
    execute_process (COMMAND git -C ${VCPKG_ROOT} pull)
    execute_process (COMMAND ${VCPKG_ROOT}/vcpkg update)
    execute_process (COMMAND ${VCPKG_ROOT}/vcpkg remove --outdated)
    execute_process (COMMAND ${VCPKG_ROOT}/vcpkg upgrade)
  endif ()
    
  set (VCPKG_EXEC ${VCPKG_ROOT}/vcpkg)
  set (VCPKG_BOOTSTRAP ${VCPKG_ROOT}/bootstrap-vcpkg.sh)

  if (NOT EXISTS ${VCPKG_ROOT}/README.md)
    message (FATAL_ERROR "***** FATAL ERROR: Could not clone vcpkg *****")
  endif ()

  if (NOT EXISTS ${VCPKG_EXEC})
    message ("Bootstrapping vcpkg in ${VCPKG_ROOT}")
    message ("Bootstrapping vcpkg in ${VCPKG_BOOTSTRAP}")
    execute_process (COMMAND ${VCPKG_BOOTSTRAP} WORKING_DIRECTORY ${VCPKG_ROOT})
  endif ()

  if (NOT EXISTS ${VCPKG_EXEC})
    message (FATAL_ERROR "***** FATAL ERROR: Could not bootstrap vcpkg *****")
  endif ()

  set (CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "")
  message (STATUS "***** Checking project third party dependencies in ${VCPKG_ROOT} *****")
  execute_process (COMMAND ${VCPKG_EXEC} install ${DEBAYER_PROJECT_DEPENDENCIES})
  message (STATUS "***** System wide intergration *****")
  execute_process (COMMAND ${VCPKG_EXEC} integrate install)
  message (STATUS "***** bash level intergration *****")
  execute_process (COMMAND ${VCPKG_EXEC} integrate bash)
  message (STATUS "***** proto installing *****")
  execute_process (COMMAND ${VCPKG_EXEC} install protobuf)
  message (STATUS "***** c-ares installing *****")
  execute_process (COMMAND ${VCPKG_EXEC} install c-ares)
  message (STATUS "***** re2 installing *****")
  execute_process (COMMAND ${VCPKG_EXEC} install re2)

  message (STATUS "***** gRPC installing *****")
  execute_process (COMMAND ${VCPKG_EXEC} install gRPC)
  message (STATUS "***** pqxx installing *****")
  execute_process (COMMAND ${VCPKG_EXEC} install libpqxx)
  message (STATUS "***** CUVI artifact installing *****")
  execute_process (COMMAND apt-get install azure-cli)
  execute_process(COMMAND az artifacts universal download -Y --organization "https://dev.azure.com/InFarm/" --project "9156b420-fe03-42c9-9d28-c26e83f94f4e" --scope project --feed "CUVI" --name "cuvi-linux" --version "1.6.2" --path .)
    execute_process (COMMAND apt-get install libxml2-dev uuid-dev)
  execute_process (COMMAND ${VCPKG_EXEC} install azure-storage-cpp)
endif ()#sudo apt-get install azure-cli
find_package(PkgConfig REQUIRED)

## Protobuf
#pkg_check_modules(Protobuf REQUIRED /home/true/vcpkg_cpptruths/packages/protobuf_x64-linux/lib/pkgconfig/protobuf.pc)
set (Protobuf_INCLUDE_DIR ${VCPKG_ROOT}/packages/protobuf_x64-linux/include)
set (Protobuf_DIR ${VCPKG_ROOT}/installed/x64-linux/share/protobuf)
set (Protobuf_MODULE_COMPATIBLE TRUE)

find_package (Protobuf QUIET CONFIG REQUIRED )
message (STATUS "Using protobuf ${Protobuf_VERSION}")
set (_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set (_REFLECTION gRPC::grpc++_reflection)


find_package (Boost REQUIRED thread log filesystem chrono)
include_directories (${Boost_INCLUDE_DIRS})
include_directories (${CMAKE_CURRENT_SOURCE_DIR})

message ("boost lib: ${Boost_LIBRARIES}, inc:${Boost_INCLUDE_DIRS}")


## gRPC
set (gRPC_DIR ${VCPKG_ROOT}/installed/x64-linux/share/grpc)
set (upb_DIR ${VCPKG_ROOT}/installed/x64-linux/share/upb)
set (absl_DIR ${VCPKG_ROOT}/installed/x64-linux/share/absl)

# set (ZLIB_DIR ${VCPKG_ROOT}/installed/x64-linux/share/zlib)
# set (ZLIB_INCLUDE_DIR ${VCPKG_ROOT}/installed/x64-linux/include)
# set (ZLIB_ROOT_DIR ${VCPKG_ROOT}/installed/x64-linux)
# find_package(ZLIB REQUIRED)

set (c-ares_DIR ${VCPKG_ROOT}/installed/x64-linux/share/c-ares)
set (c-ares_INCLUDE_DIR ${VCPKG_ROOT}/installed/x64-linux/include)
set (c-ares_ROOT_DIR ${VCPKG_ROOT}/installed/x64-linux)
find_package(c-ares CONFIG REQUIRED)

set (OPENSSL_DIR ${VCPKG_ROOT}/installed/x64-linux/share/openssl)
set (OPENSSL_INCLUDE_DIR ${VCPKG_ROOT}/installed/x64-linux/include)
set (OPENSSL_ROOT_DIR ${VCPKG_ROOT}/installed/x64-linux)
find_package(OpenSSL REQUIRED)

set (re2_DIR ${VCPKG_ROOT}/installed/x64-linux/share/re2)
find_package(re2 REQUIRED)

set (GRPC_INCLUDE_DIR ${VCPKG_ROOT}/installed/x64-linux/include)

find_package (gRPC CONFIG REQUIRED)
message (STATUS "Using gRPC ${grpc_VERSION}")
set(_GRPC_GRPCPP gRPC::grpc++)

## Install the executable to <install_directory>/bin
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
## Install libraries (if any) to <install_directory>/bin
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

###################################################################################

## Source file containing the "main" function
set (MAIN_SOURCES main.cpp)
## Specify a name for the generated executable file
set (MAIN_EXE_NAME ${PROJECT_NAME})

add_subdirectory ("Logging")
add_subdirectory ("proto")
add_subdirectory ("gRPC")
add_subdirectory ("psqlDebayer")
add_subdirectory ("UUID")
add_subdirectory ("Blob")
add_subdirectory ("RawImageProcessor")
add_subdirectory ("CUVI")
add_subdirectory ("hashAlgorithms")
find_package(ZLIB REQUIRED)


#message (STATUS "***** azure-storage-cpp installing *****")
#execute_process (COMMAND ${VCPKG_EXEC} update)
#execute_process (COMMAND ${VCPKG_EXEC} install azure-storage-cpp)


## 1. Compile...
add_executable (${PROJECT_NAME} main.cpp)
target_include_directories (${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS} ${grpc_INCLUDE_DIRS} ${Protobuf_INCLUDE_DIRS} ${UUID_INCLUDE_DIRS} "/usr/include")
#target_link_directories(${PROJECT_NAME} ${WASTORAGE_LIBRARY} ${VCPKG_ROOT}/installed/x64-linux/share/azure-storage-cpp/")

# ## 2. Link...
target_link_libraries (debayer
    ${Boost_LIBRARIES}
    #Boost::uuid
    UUID
    RawImageProcessor
    ${grpc_LIBRARIES}
    logging 
    fileStream
    grpcServer
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    hashAlgorithms
    )

#foreach(_target
#  greeter_client greeter_server
#  greeter_async_client greeter_async_client2 greeter_async_server)
#  add_executable(${_target} "${_target}.cc"
#    ${hw_proto_srcs}
#    ${hw_grpc_srcs})
#  target_link_libraries(${_target}
#    ${_REFLECTION}
#    ${_GRPC_GRPCPP}
#    ${_PROTOBUF_LIBPROTOBUF})
#endforeach()

## 3. Install...
# install( TARGETS ${MAIN_EXE_NAME} RUNTIME DESTINATION bin )
