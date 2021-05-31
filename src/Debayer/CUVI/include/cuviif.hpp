#ifndef CUVIIF_HPP
#define CUVIIF_HPP

#ifndef __cplusplus
#error This Header Requires A C++ Compiler
#endif

#include "cuviCore.hpp"

namespace cuvi { namespace imageFiltering
{
	CUVI_EXPORTS CuviStatus imageFilter(const CuviImage& src, CuviImage& dst, const CuviFilter& filter, const CuviStream& stream = CuviStream());
		
	CUVI_EXPORTS CuviStatus imageFilter(const CuviImage& src, CuviImage& dst, const CuviRect& roi, const CuviFilter& filter, bool copyOutliers = true, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus minFilter(const CuviImage& src, CuviImage& dst, const CuviRect& roi, const CuviSize& filterSize, const CuviStream& stream = CuviStream());
		
	CUVI_EXPORTS CuviStatus maxFilter(const CuviImage& src, CuviImage& dst, const CuviRect& roi, const CuviSize& filterSize, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus imageGradients(const CuviImage& src, CuviImage& gradX, CuviImage& gradY, const CuviGradientKernelType type = CUVI_GRADIENT_SOBEL_3x3, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus medianFilter(const CuviImage& src, CuviImage& dst, const CuviRect& roi, const CuviSize& filterSize = CuviSize(3, 3), const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus modeFilter(const CuviImage& src, CuviImage& dst, const CuviRect& roi, const CuviSize& filterSize = CuviSize(3, 3), const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus underwaterFilter(const CuviImage& src, CuviImage& dst, CuviEnhancementParams params = CuviEnhancementParams(), const CuviStream& stream = CuviStream());
}}

#endif
