// Standard Libs
#include <iostream>

// InFarm libs
#include <Logging/Logging.h>
#include <gRPC/gRPCServer.h>

// External Libs
//#include <boost/filesystem.hpp>
//#include <boost/program_options.hpp>
#include "RawImageProcessor/RawImageProcessor.h"
// Namespaces
using namespace std;

int main(int, char* [])
{
    RawImageProcessor RIP;
	// Start the application logging as soon as the application start
    init_logging();
    // TODO: Get the host name that the service is being run on and add to the log.
    BOOST_LOG_TRIVIAL(info) << "Debayer Service started" << endl;
    BOOST_LOG_TRIVIAL(info) << "Starting gRPC server" << endl;

	//TODO
    return 0;
}
