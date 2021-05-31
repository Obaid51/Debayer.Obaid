#include "ImageMeta.h"


void Image_Meta::setImageRealBitDepth(__int64 bit_depth)
{
	image_bit_depth_real_ = bit_depth;
}

void Image_Meta::setImageBitDepth(__int64 bit_depth)
{
	image_bit_depth_ = bit_depth;
}

void Image_Meta::setImageWidth(__int64 width)
{
	image_width_ = width;
}

void Image_Meta::setImageHeight(__int64 height)
{
	image_height_ = height;
}

void Image_Meta::setImageSizeBytes(__int64 size)
{
	image_size_bytes_ = size;
}

void Image_Meta::setTimeStamp(const time_t seconds, const double milliseconds, const double microseconds)
{
	time_stamp_ = Time_Stamp();
	time_stamp_.seconds = seconds;
	time_stamp_.milliseconds = milliseconds;
	time_stamp_.microseconds = microseconds;
}


long long Image_Meta::getImageRealBitDepth()
{
	return image_bit_depth_real_;
}

long long Image_Meta::getImageBitDepth()
{
	return image_bit_depth_;
}

long long Image_Meta::getImageWidth()
{
	return image_width_;
}

long long Image_Meta::getImageHeight()
{
	return image_height_;
}

__int64 Image_Meta::getImageSizeBytes()
{
	return image_size_bytes_;
}

__int64 Image_Meta::getTimeStamp()
{
	// TODO: Convert the timestamp into a UTC ms timestamp
	return 0;
}
