#ifndef CUVICO_HPP
#define CUVICO_HPP

#ifndef __cplusplus
#error This Header Requires A C++ Compiler
#endif

#include "cuviCore.hpp"

namespace cuvi { namespace colorOperations
{
	
	CUVI_EXPORTS CuviStatus channelSplit(const CuviImage& src, CuviImage& red, CuviImage& green, CuviImage& blue, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus channelMerge(const CuviImage& red, const CuviImage& green, const CuviImage& blue, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus adjust(CuviImage& srcDst, const CuviScalar& low_in = 0.0f, const CuviScalar& high_in = 1.0f, const CuviScalar& low_out = 0.0f, const CuviScalar& high_out = 1.0f, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus channelMix(const CuviImage& src, CuviImage& dst, Cuvi32f coeffs[12], const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus autoColor(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus LUT(const CuviImage& src, const CuviImage& mapping, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus histEq(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus rgb2gray(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus rgb2gray(const CuviImage& src, CuviImage& dst, const CuviScalar& coeffs, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus gray2rgb(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus gray2rgb(CuviImage& srcDst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus rgb2yuv(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus yuv2rgb(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus rgb2ycbcr(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus rgb2yuv422(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus ycbcr2rgb(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus demosaic(const CuviImage& src, CuviImage& dst, const CuviBayerSeq sensorAlignment, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus demosaicDFPD(const CuviImage& src, CuviImage& dst, const CuviBayerSeq sensorAlignment, const bool refineResults = false, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus borderMask(const CuviImage& src, CuviImage& dst, const Cuvi32s top, const Cuvi32s bottom, const Cuvi32s left, const Cuvi32s right, const Cuvi32f* mask, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus imageBinary(const CuviImage& src, CuviImage& dst, const Cuvi32f threshold = 0.5f, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus colorPick(const CuviImage& src, CuviImage& dst, const CuviColor color, const Cuvi32f threshold = 128.0f, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus logTransform(const CuviImage& src, CuviImage& dst, const Cuvi32f c = 1.0f, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus gammaCorrect(const CuviImage& src, CuviImage& dst, const Cuvi32f gamma = 1.0f, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus rgb2hsv(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus hsv2rgb(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus rgb2Lab(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus Lab2rgb(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus blackGammaLUT(const CuviImage& src, CuviImage& dst, Cuvi16u* redLUT, Cuvi16u* greenLUT, Cuvi16u* blueLUT, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus FPNCorrection(const CuviImage& src, CuviImage& dst, const CuviImage& white, const CuviImage& black, Cuvi32f gain, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus V210TOYUV444(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus YUV422TOV210(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus YUV444TOV210(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus fpn(CuviImage &output, const CuviImage &input, const CuviImage &blackImage);

	CUVI_EXPORTS CuviStatus dehaze(const CuviImage& src, CuviImage& dst, int max0, int max1, int max2, const CuviStream& stream = CuviStream());
	
	CUVI_EXPORTS CuviStatus lowlight(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());


}}

#endif
