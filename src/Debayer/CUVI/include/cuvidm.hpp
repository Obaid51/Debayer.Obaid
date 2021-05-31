#ifndef CUVIDM_HPP
#define CUVIDM_HPP

#ifndef __cplusplus
#error This Header Requires A C++ Compiler
#endif

#include "cuviCore.hpp"

namespace cuvi
{ 
	namespace device 
	{

		CUVI_EXPORTS Cuvi32s getDeviceCount();

		CUVI_EXPORTS Cuvi32s getCurentDevice();

		CUVI_EXPORTS CuviStatus setCurrentDevice(const Cuvi32s deviceID);

		CUVI_EXPORTS CuviStatus	syncCurrentDevice();

		CUVI_EXPORTS CuviStatus resetCurrentDevice();

		CUVI_EXPORTS CuviStatus getDeviceProperties(const int deviceID, CuviDeviceProperties& props);
	}	
}



#endif
