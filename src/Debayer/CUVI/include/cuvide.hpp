#ifndef CUVIDE_HPP
#define CUVIDE_HPP

#include "cuviCore.hpp"

namespace cuvi { namespace dataExchange
{
	CUVI_EXPORTS CuviStatus bitConversion(const CuviImage& src, const CuviImage& dst, const CuviStream& stream = CuviStream());
	
	CUVI_EXPORTS CuviStatus padImage(const CuviImage& src, CuviImage& dst, const Cuvi32s top, const Cuvi32s bottom, const Cuvi32s left, const Cuvi32s right, const Cuvi32f* values, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus generateRandomImage(CuviImage& src, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus convertScale(const CuviImage& src, CuviImage& dst, const Cuvi32f scale = 1.0f, const Cuvi32f offset = 0.0f, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus threshold(const CuviImage& src, CuviImage& dst, const CuviScalar& minThresh, const CuviScalar& maxThresh, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus rectangle(CuviImage& image, const CuviRect& rect, const CuviScalar& color, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus getChannel(const CuviImage& src, CuviImage& dst, const Cuvi32s channel, const CuviStream& stream = CuviStream());
}}

#endif
