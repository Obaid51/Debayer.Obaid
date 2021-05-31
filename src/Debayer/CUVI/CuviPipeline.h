/*
///////////// Complete Desired Pipeline ////////////////
1.              De-sequence (norpix .seq file)
2.              Bad pixel correction
3.              Dark frame subtraction
4.              Flat-Filed correction (if you can get calibration data for FFC)
5.              White balance
6.              Exposure correction
7.              Debayer
8.              Colour correction
9.              Denoising
10.             Rotation
11.             Curves and Levels via 1D LUT
12.             Sharpening
13.             Colour grading with 3D LUT
14.             Gamma corrections
15.             Colour space adjustments
16.             Export to tiff
*/

#pragma once

#include "include/cuvi.h"
#include "include/cuviCore.hpp"
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include "../Logging/Logging.h"
#include "ImageMeta.h"

using namespace std;

class cuvi_pipeline
{
private:
	CuviStatus histogram_equalisation(CuviImage& input, CuviImage& output);
	CuviStatus lut(CuviImage& input, CuviImage& output, string input_lut);
	CuviStatus demosaic_dfpd(CuviImage& input, CuviImage& output);
	CuviStatus bit_conversion(CuviImage& input, CuviImage& output, int input_bitness, int output_bitness);
	CuviStatus image_filter(CuviImage& input, CuviImage& output);
	CuviStatus channel_mix(CuviImage& input, CuviImage& output);
	CuviStatus image_colour_filter(CuviImage& input, CuviImage& output);
	CuviStatus black_gamma_lut(CuviImage& input, CuviImage& output, string input_lut);
	CuviStatus gamma_correct(CuviImage& input, CuviImage& output);
	CuviStatus increase_saturation(CuviImage& input, CuviImage& output);
	CuviStatus offset_channel(CuviImage& input, CuviImage& output);
	CuviStatus stretch_channel(CuviImage& input, CuviImage& output);
	CuviStatus stretch_max_and_min(CuviImage& input, CuviImage& output);
	CuviStatus log_transform(CuviImage& input, CuviImage& output, float c);

	CuviStatus setup_input(Image_Meta& image_meta, CuviImage& input);

	CuviStatus pre_debayer_pipeline(CuviImage& input, CuviImage& output);
	CuviStatus post_debayer_pipeline(CuviImage& input, CuviImage& output, Image_Meta& image_meta);

public:	
	CuviStatus run_pipeline(const string output_file_path, void* frame_buffer, Image_Meta& image_meta);
};
