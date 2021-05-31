#ifndef CUVIIS_HPP
#define CUVIIS_HPP

namespace cuvi
{
	namespace imageStatistics
	{
		CUVI_EXPORTS CuviStatus sum(const CuviImage& src, CuviScalar& sum, const CuviStream& stream = CuviStream());
		
		CUVI_EXPORTS CuviStatus mean(const CuviImage& src, CuviScalar& mean, const CuviStream& stream = CuviStream());
		
		CUVI_EXPORTS CuviStatus meanStdDev(const CuviImage& src, CuviScalar& meanValue, CuviScalar& stdDevValue, const CuviStream& stream = CuviStream());
		
		CUVI_EXPORTS CuviStatus min(const CuviImage& src, CuviScalar& minValue, const CuviStream& stream = CuviStream());
		
		CUVI_EXPORTS CuviStatus max(const CuviImage& src, CuviScalar& maxValue, const CuviStream& stream = CuviStream());
		
		CUVI_EXPORTS CuviStatus minMax(const CuviImage& src, CuviScalar& minValue, CuviScalar& maxValue, const CuviStream& stream = CuviStream());
		
		CUVI_EXPORTS CuviStatus countInRange(const CuviImage& src, CuviScalar& count, const CuviScalar& rangeMin, const CuviScalar& rangeMax, const CuviStream& stream = CuviStream());

		CUVI_EXPORTS CuviStatus calcHist(const CuviImage& src, CuviHistogram& hist, const CuviStream& stream = CuviStream());
	}
}

#endif