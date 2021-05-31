#ifndef CUVICV_HPP
#define CUVICV_HPP

#ifndef __cplusplus
#error This Header Requires A C++ Compiler
#endif

#include "cuviCore.hpp"

namespace cuvi { namespace computerVision
{
	CUVI_EXPORTS CuviStatus goodFeaturesToTrack(const CuviImage& src, const CuviRect& roi, CuviPointValue2D<float, float>*& output, Cuvi32s& maxFeatures, const CuviFeaturesCriteria criteria = CuviFeaturesCriteria(), const CuviStream& stream = CuviStream());
	
	CUVI_EXPORTS CuviStatus trackFeatures(const CuviImage& previous, const CuviImage& next, CuviPointValue2D<Cuvi32f, Cuvi32f>* inputFeatures, CuviPointValue2D<Cuvi32f, Cuvi32f>*& trackedFeatures, const Cuvi32s featureCount, const CuviTrackingCriteria criteria, const CuviStream& stream = CuviStream());
		
	CUVI_EXPORTS CuviStatus opticalFlowPyrLKDense(const CuviImage& previous, const CuviImage& next, Cuvi32f* flowX, Cuvi32f* flowY, const CuviTrackingCriteria criteria, const CuviStream& stream = CuviStream());
		
	CUVI_EXPORTS CuviStatus opticalFlowHS(const CuviImage& previous, const CuviImage& next, Cuvi32f* flowX, Cuvi32f* flowY, const bool usePrevious, const Cuvi32f lambda = 1.0f, const Cuvi32s iterations = 1, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus focusStack(CuviImage* images, const int numImages, CuviImage& stack, const CuviFilter denoiseFilter = CuviSpecialFilters::gaussian(CuviSize(15, 15), 5.0f), const CuviStream& stream = CuviStream());
		
	//CUVI_EXPORTS CuviStatus	minEigenVals(CuviImage* srcImage, CuviImage* minEigenVals,CuviGradientKernelType gradientKernelType = CUVI_GRADIENT_SOBEL_3x3, Cuvi32s windowSize = 3, CuviStream* stream = NULL);
		
	//CUVI_EXPORTS CuviStatus	eigenValsVecs(CuviImage* srcImage, CuviImage* eigenValsVecs,CuviGradientKernelType gradientKernelType = CUVI_GRADIENT_SOBEL_3x3, Cuvi32s windowSize = 3, CuviStream* stream = NULL);
}}

#endif
