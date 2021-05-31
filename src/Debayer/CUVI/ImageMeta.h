#pragma once
#include <ctime>
#include "cpprest/details/SafeInt3.hpp"
//#define __int64 __int64_t

class Image_Meta {
private:
	// TODO: Reevaluate if the need to use a int64, or a uShort will suffice for this project
	__int64 image_bit_depth_real_ = 0;
	__int64 image_bit_depth_ = 0;
	__int64 image_width_ = 0;
	__int64 image_height_ = 0;
	__int64 image_size_bytes_ = 0;

	struct Time_Stamp
	{
		time_t          seconds;        // (4 bytes)
		double          milliseconds;   // (2 bytes)
		double          microseconds;   // (2 bytes)
	};
	
	Time_Stamp time_stamp_;

	// TODO: Fill in these methods

public:
	void setImageRealBitDepth(__int64 bit_depth);
	void setImageBitDepth(__int64 bit_depth);
	void setImageWidth(__int64 width);
	void setImageHeight(__int64 height);
	void setImageSizeBytes(__int64 size);
	void setTimeStamp(time_t seconds, double milliseconds, double microseconds);

	__int64 getImageRealBitDepth();
	__int64 getImageBitDepth();
	__int64 getImageWidth();
	__int64 getImageHeight();
	__int64 getImageSizeBytes();
	__int64 getTimeStamp();
};
