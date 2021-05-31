#pragma once

// Standard Libs
#include <iostream>
#include <memory>
#include <string>
#include <deque>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
///delete
// InFarm Libs
#include <proto/FileStream.grpc.pb.h>
#include <proto/FileStream.pb.h>
#include <Logging/Logging.h>
#include "buffer.h"
#include "hashAlgorithms/hashAlgorithms.h"
#include <utility>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using namespace::std;

// Health checks for the service.
using filestream::Health;

// Functionality that the service provides
using filestream::Transfer;
using filestream::MaxSize;




void RunGrpcServer(ImageBuffer*);
