#include "CuviPipeline.h"

CuviStatus cuvi_pipeline::histogram_equalisation(CuviImage& input, CuviImage& output)
{
	CuviImage hsv = CuviImage(input.size(), 8, 3);
	CuviImage h, h_eq, s, v;
	cuvi::colorOperations::rgb2hsv(input, hsv);
	cuvi::colorOperations::channelSplit(hsv, h, s, v);
	cuvi::colorOperations::histEq(h, h_eq);
	cuvi::colorOperations::channelMerge(h_eq, s, v, hsv);
	CuviStatus status = cuvi::colorOperations::hsv2rgb(hsv, output);
	return status;
}

CuviStatus cuvi_pipeline::lut(CuviImage& input, CuviImage& output, string InputLUT = "") {
	//LUT Parameters
	BOOST_LOG_TRIVIAL(debug) << "Performing LUT to RAW..." << endl;
	const int mappingSize = 4096;
	Cuvi16u LUT[mappingSize];
	CuviImage mapping(mappingSize, 1, CUVI_16UC1);


	if (InputLUT == "" || InputLUT == "Linear" || InputLUT == "1" || InputLUT == "L") {
		BOOST_LOG_TRIVIAL(debug) << "Creating a linear LUT" << endl;

		for (int i = 1; i < mappingSize; i = i + 1)
		{
			LUT[i] = (unsigned short)i;
		}

		mapping.upload(LUT);
	}
	else if (InputLUT == "slight" || InputLUT == "s")
	{
		BOOST_LOG_TRIVIAL(debug) << "Creating a slight LUT" << endl;

		for (int i = 1; i < mappingSize; i = i + 1)
		{
			LUT[i] = (unsigned short)pow((double)(pow(-8, -8) * i), (double)3) + pow((double)(0.0005 * i), (double)2) + (0.348 * i) + 0.6422;
			//y = 1E-07x3 - 0.0008x2 + 2.0432x - 1.0275
		}

		mapping.upload(LUT);
	}
	ifstream ifs(InputLUT);
	if (ifs.is_open()) {

		int n = 0;
		int number = 0;
		string t;
		while (getline(ifs, t)) {
			number = stoi(t);
			LUT[n] = (unsigned short)number;
			++n;
		}
		BOOST_LOG_TRIVIAL(debug) << "The file contains " << n << " lines for LUT." << endl;
		//Create and upload LUT matrix on device
		mapping.upload(LUT);
		//LUT
	}
	ifs.close();
	CuviStatus status = cuvi::colorOperations::LUT(input, mapping, output);
	return status;
}

CuviStatus cuvi_pipeline::demosaic_dfpd(CuviImage& input, CuviImage& output) {
	BOOST_LOG_TRIVIAL(debug) << "Performing Debayer DFPD..." << endl;
	//demosaic_dfpd Parameters
	CuviBayerSeq bayerPattern = CuviBayerSeq::CUVI_BAYER_RGGB;
	//demosaic_dfpd
	CuviStatus status = cuvi::colorOperations::demosaicDFPD(input, output, bayerPattern, true);
	return status;
}

CuviStatus cuvi_pipeline::bit_conversion(CuviImage& input, CuviImage& output, int input_bitness = 12, int output_bitness = 16) {
	BOOST_LOG_TRIVIAL(debug) << "Performing Bit Conversion from " << input_bitness << " bit data to " << output_bitness << " bit data..." << endl;
	//bit_conversion Parameters:
	//CuviImage input_out;
	//cuvi::dataExchange::convertScale(input, input_out, 0.5f); 
	output.release();
	CuviStatus status;
	if (output_bitness == 32)
	{
		status = output.create(input.width(), input.height(), CUVI_32FC3);
	}
	else if (output_bitness == 16)
	{
		status = output.create(input.width(), input.height(), CUVI_16UC3);
	}
	else if (output_bitness == 8)
	{
		status = output.create(input.width(), input.height(), CUVI_8UC3);
	}
	else
	{
		status = output.create(input.width(), input.height(), CUVI_16UC3);
	}
	input.setDataBits(input_bitness);
	output.setDataBits(output_bitness);
	if (status != CUVI_SUCCESS) return status;
	//bit_conversion
	status = cuvi::dataExchange::bitConversion(input, output);
	input.release();
	if (output_bitness == 32)
	{
		status = input.create(output.width(), output.height(), CUVI_32FC3);
	}
	else if (output_bitness == 16)
	{
		status = input.create(output.width(), output.height(), CUVI_16UC3);
	}
	else if (output_bitness == 8)
	{
		status = input.create(output.width(), output.height(), CUVI_8UC3);
	}
	else
	{
		status = input.create(output.width(), output.height(), CUVI_16UC3);
	}
	input.setDataBits(output_bitness);
	output.setDataBits(output_bitness);
	return status;
}

CuviStatus cuvi_pipeline::image_filter(CuviImage& input, CuviImage& output) {
	BOOST_LOG_TRIVIAL(debug) << "Performing Filter: 5x5 Sharpening..." << endl;
	//Filter - Average
	Cuvi32f coeffs[9] = {
						1 / 9.0f, 1 / 9.0f, 1 / 9.0f,
						1 / 9.0f, 1 / 9.0f, 1 / 9.0f,
						1 / 9.0f, 1 / 9.0f, 1 / 9.0f,
	};
	CuviFilter Average(3, 3, coeffs);

	//Filter - Sharp
	float ls_coefs[] = {
				0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, -2.0f / 16, -1.0f / 16, -1.0f / 16, -2.0f / 16,
				0.0f, -1.0f / 16, 1.0f, 5.0f / 16, -1.0f / 16,
				0.0f, -1.0f / 16, 5.0f / 16, 6.0f / 16, -1.0f / 16,
				0.0f, -2.0f / 16, -1.0f / 16, -1.0f / 16, -2.0f / 16
	};
	CuviFilter LumaSharpMat(5, 5, ls_coefs);        //    5x5 Filter for Luma Sharpening

	//image_filter
	CuviStatus status = cuvi::imageFiltering::imageFilter(input, output, LumaSharpMat);
	return status;
}

CuviStatus cuvi_pipeline::channel_mix(CuviImage& input, CuviImage& output) {
	BOOST_LOG_TRIVIAL(debug) << "Performing Color Correction via Channel Mix..." << endl;
	//channel_mix Parameters
	//float coeffs[12] = {
	//				 1.05, -0.025f, -0.025f, 0.0f,
	//				 -0.45f, 1.975f, -0.525f, 0.0f,
	//				 0.225f, -1.05f, 1.825f, 0.0f
	//};
	Cuvi32f coeffs[12] = {
			1.32f,        -0.46f,        0.14f,	0.0f,
		-0.36f,         1.25f,        0.11f,	0.0f,
			0.08f,        -1.96f,        1.88f,	0.0f
	};
	CuviStatus status = cuvi::colorOperations::channelMix(input, output, coeffs);
	return status;
}

CuviStatus cuvi_pipeline::image_colour_filter(CuviImage& input, CuviImage& output)
{
	CuviRect roi(0, 0, input.width(), input.height());
	Cuvi32f coeffs[9] = {
		1.32f,         -0.46f,        0.14f,
		-0.36f,         1.25f,        0.11f,
			0.08f,        -1.96f,        1.88f
	};

	CuviFilter f(3, 3, coeffs);
	CuviStatus status = cuvi::imageFiltering::imageFilter(input, output, roi, f);
	return status;
}

CuviStatus cuvi_pipeline::black_gamma_lut(CuviImage& input, CuviImage& output, string input_lut = "") {
	BOOST_LOG_TRIVIAL(debug) << "Performing 3D LUT to Each Channel Separately";
	//black_gamma_lut Parameters
	const int mappingSize = 65536;
	Cuvi16u* redLUT = new Cuvi16u[mappingSize];
	Cuvi16u* greenLUT = new Cuvi16u[mappingSize];
	Cuvi16u* blueLUT = new Cuvi16u[mappingSize];

	ifstream ifs(input_lut);
	if (input_lut == "" || input_lut == "Linear" || input_lut == "1" || input_lut == "L") {
		BOOST_LOG_TRIVIAL(debug) << "Creating a linear LUT";
		ifs.close();
		BOOST_LOG_TRIVIAL(debug) << "Failed to open the file, using default values";

		for (int i = 1; i < mappingSize; i = i + 1)
		{
			redLUT[i] = i;
			greenLUT[i] = i;
			blueLUT[i] = i;
		}
	}
	else {
		int n = 0;
		int number = 0;
		string t;
		while (getline(ifs, t)) {
			number = stoi(t);
			redLUT[n] = greenLUT[n] = blueLUT[n] = number;
			++n;
		}
		ifs.close();
		BOOST_LOG_TRIVIAL(debug) << "The file contains " << n << " lines for LUT";
	}
	CuviStatus status = cuvi::colorOperations::blackGammaLUT(input, output, redLUT, greenLUT, blueLUT);
	delete[] redLUT;
	delete[] greenLUT;
	delete[] blueLUT;
	return status;
}

CuviStatus cuvi_pipeline::gamma_correct(CuviImage& input, CuviImage& output) {
	BOOST_LOG_TRIVIAL(debug) << "Performing Gamma Correction...";
	//gamma_correct Parameters
	Cuvi32f gamma = 0.8f;

	//gamma_correct
	CuviStatus status = cuvi::colorOperations::gammaCorrect(input, output, gamma);
	return status;
}

CuviStatus cuvi_pipeline::increase_saturation(CuviImage& input, CuviImage& output)
{
	CuviStatus status;
	CuviImage intermediate_frame, hsv, h, s, v, s_increased;
	const int mappingSize = 256;
	Cuvi16u* LUT = new Cuvi16u[mappingSize];
	CuviImage* mapping = new CuviImage(mappingSize, 1, CUVI_16UC1);

	intermediate_frame = CuviImage(input.size(), CUVI_DEPTH_32F, input.channels());
	cuvi::dataExchange::convertScale(input, intermediate_frame);

	status = cuvi::colorOperations::rgb2hsv(intermediate_frame, hsv);
	intermediate_frame.release();
	intermediate_frame = CuviImage(input.size(), CUVI_DEPTH_8U, input.channels());
	cuvi::dataExchange::convertScale(hsv, intermediate_frame);
	status = cuvi::colorOperations::channelSplit(intermediate_frame, h, s, v);

	for (int i = 1; i < mappingSize; i = i + 1)
	{
		LUT[i] = i; // (unsigned short) (pow((double)(-00000.2 * i), (double)2) + (2.018 * i)) / 256;
		//y = -2E-05x2 + 2.018x
	}

	mapping->upload(LUT);
	status = cuvi::colorOperations::LUT(s, *mapping, s_increased);
	status = cuvi::colorOperations::channelMerge(h, s_increased, v, intermediate_frame);

	cuvi::dataExchange::convertScale(intermediate_frame, hsv);
	intermediate_frame.release();
	status = cuvi::colorOperations::hsv2rgb(hsv, intermediate_frame);

	cuvi::dataExchange::convertScale(intermediate_frame, output);

	delete[] LUT;
	delete mapping;
	~intermediate_frame;
	return status;
}

CuviStatus cuvi_pipeline::offset_channel(CuviImage& input, CuviImage& output)
{
	CuviStatus status;
	CuviScalar max;
	CuviScalar min;
	cuvi::imageStatistics::minMax(input, min, max);
	Cuvi32f	offset = 0;
	if (input.channels() == 1)
	{
		offset = *min.vals();
	}
	else
	{
		for (int i = 0; i < input.channels(); i++)
		{
			if (min.vals()[i] > offset)
			{
				offset = min.vals()[i];
			}
		}
	}
	offset = -offset;
	status = cuvi::dataExchange::convertScale(input, output, 1.0f, offset);
	return status;
}

CuviStatus cuvi_pipeline::stretch_channel(CuviImage& input, CuviImage& output)
{
	CuviStatus status;
	CuviScalar max, min;
	cuvi::imageStatistics::minMax(input, min, max);

	float max_image_value;
	if (input.depth() == 32)
	{
		max_image_value = 1;
	}
	else if (input.depth() == 16)
	{
		max_image_value = 65536;
	}
	else if (input.depth() == 8)
	{
		max_image_value = 256;
	}
	else
	{
		max_image_value = 256;
	}

	Cuvi32f	max_pixel = max_image_value;
	if (input.channels() == 1)
	{
		max_pixel = *max.vals();
	}
	else
	{
		for (int i = 0; i < input.channels(); i++)
		{
			//BOOST_LOG_TRIVIAL(debug) << max.vals()[i] << std::endl;
			if (max.vals()[i] < max_pixel)
			{
				max_pixel = max.vals()[i];
			}
		}
	}
	Cuvi32f scale = max_image_value / max_pixel;
	status = cuvi::dataExchange::convertScale(input, output, scale, 0.0f);
	return status;
}

CuviStatus cuvi_pipeline::stretch_max_and_min(CuviImage& input, CuviImage& output)
{
	CuviStatus status;
	CuviImage intermediate_frame;
	CuviScalar max, min;

	status = offset_channel(input, intermediate_frame);
	status = stretch_channel(intermediate_frame, input);


	CuviImage hsv, h, s, v;
	intermediate_frame.release();
	intermediate_frame = CuviImage(input.size(), CUVI_DEPTH_32F, input.channels());
	cuvi::dataExchange::convertScale(input, intermediate_frame, 1.0f / 65536.0f);

	cuvi::imageStatistics::minMax(intermediate_frame, min, max);

	status = cuvi::colorOperations::rgb2hsv(intermediate_frame, hsv);
	status = cuvi::colorOperations::channelSplit(hsv, h, s, v);
	intermediate_frame.release();
	status = offset_channel(v, intermediate_frame);
	status = stretch_channel(intermediate_frame, v);
	status = cuvi::colorOperations::channelMerge(h, s, v, hsv);

	cuvi::imageStatistics::minMax(hsv, min, max);

	intermediate_frame.release();
	status = cuvi::colorOperations::hsv2rgb(hsv, intermediate_frame);
	cuvi::dataExchange::convertScale(intermediate_frame, output, 65536.0f);

	cuvi::imageStatistics::minMax(intermediate_frame, min, max);

	~intermediate_frame;
	return status;
}

CuviStatus cuvi_pipeline::log_transform(CuviImage& input, CuviImage& output, float c)
{
	CuviStatus status;
	CuviScalar max, min;
	CuviImage intermediate_frame = CuviImage(input.size(), CUVI_DEPTH_32F, input.channels());
	status = cuvi::dataExchange::convertScale(input, intermediate_frame, 1.0f / 65536.0f);
	input.release();
	status = cuvi::colorOperations::logTransform(intermediate_frame, input, c);
	cuvi::imageStatistics::minMax(intermediate_frame, min, max);
	float max_image_value = 65536;
	Cuvi32f	max_pixel = max_image_value;
	for (int i = 0; i < input.channels(); i++)
	{
		//BOOST_LOG_TRIVIAL(debug) << max.vals()[i] << std::endl;
		if (max.vals()[i] < max_pixel)
		{
			max_pixel = max.vals()[i];
		}
	}
	Cuvi32f scale = max_image_value / max_pixel;
	status = cuvi::dataExchange::convertScale(input, output, scale);

	return status;
}

CuviStatus cuvi_pipeline::setup_input(Image_Meta& image_meta, CuviImage& input)
{
	Cuvi32s width = image_meta.getImageWidth();
	Cuvi32s height = image_meta.getImageHeight();
	CuviSize size = CuviSize(width, height);
	Cuvi32s bitness = image_meta.getImageBitDepth();
	
	input.create(size, bitness, 1);
	int pitch = image_meta.getImageWidth() * 2;


	void* frame = malloc(image_meta.getImageSizeBytes());
	
	CuviStatus status = input.upload(frame, pitch);
	return status;
}

CuviStatus cuvi_pipeline::pre_debayer_pipeline(CuviImage& input, CuviImage& output)
{
	// FPN or Flat Field Correction required the use of a static input "Whiteframe". The blackFrame is to be emebedded into each seq file. It is to be the first and the last frame of the seq file.
	//Cuvi32f gain = 100;
	//status = cuvi::colorOperations::FPNCorrection(input, output, whiteFrame, blackFrame, gain);

	//LUT - LUT on RAW
	CuviStatus status = lut(input, output);
	input.release();
	~input;
	return status;
}

CuviStatus cuvi_pipeline::post_debayer_pipeline(CuviImage& input, CuviImage& output, Image_Meta& image_meta)
{
	return CuviStatus();
}

CuviStatus cuvi_pipeline::run_pipeline(const string output_file_path, void* frame_buffer, Image_Meta& image_meta)
{
	CuviImage input, OutputAlpha, OutputBravo;
	CuviStatus status = setup_input(image_meta, input);
	if (status != CUVI_SUCCESS)	goto exit;

	// TODO: Create a better system to extract only the frame logs.
	if (output_file_path != "")
	{
		status = pre_debayer_pipeline(input, OutputAlpha);
		~input;
		if (status != CUVI_SUCCESS)	goto exit;

		//demosaic_dfpd
		status = demosaic_dfpd(OutputAlpha, OutputBravo);
		if (status != CUVI_SUCCESS)	goto exit;
		OutputAlpha.release();

		//bit_conversion - 12 bit to 16 bit
		int input_bitness = image_meta.getImageRealBitDepth();
		int output_bitness = image_meta.getImageBitDepth();
		status = bit_conversion(OutputBravo, OutputAlpha, input_bitness, output_bitness);
		if (status != CUVI_SUCCESS)	goto exit;

		status = stretch_max_and_min(OutputAlpha, OutputBravo);
		if (status != CUVI_SUCCESS)	goto exit;

		//channel_mix - Color Improvement
		//status = image_colour_filter(output2, output);
		//if (status != CUVI_SUCCESS)	printf("\nchannel_mix Error: %d", status);

		//status = increase_saturation(output2, output);

		//image_filter - Sharp
		status = image_filter(OutputBravo, OutputAlpha);
		if (status != CUVI_SUCCESS)	goto exit;

		//black_gamma_lut - 3D LUT (Separate for each channel)
		//status = black_gamma_lut(output2, output);
		//if (status != CUVI_SUCCESS)	printf("\nblack_gamma_lut Error: %d", status);

		status = log_transform(OutputAlpha, OutputBravo, 1.4f);
		if (status != CUVI_SUCCESS)	goto exit;

		status = bit_conversion(OutputBravo, OutputAlpha, 16, 8);
		if (status != CUVI_SUCCESS)	goto exit;

		status = cuvi::colorOperations::autoColor(OutputAlpha, OutputBravo);
		if (status != CUVI_SUCCESS)	goto exit;

		cuvi::colorOperations::adjust(OutputBravo);

		//cuvi::io::saveImage(OutputBravo, output_file_path);
		CuviImageFormat image_codec = CuviImageFormat::CUVI_JPEG;
		// TODO: Have the quality be settable from an ENV var
		cuvi::codecs::encode(OutputBravo, image_codec, output_file_path,70);
	}
	goto exit;

exit:
	OutputAlpha.release();
	OutputBravo.release();
	return status;
}
