#ifndef CUVIIT_HPP
#define CUVIIT_HPP

#ifndef __cplusplus
#error This Header Requires A C++ Compiler
#endif

#include "cuviCore.hpp"

namespace cuvi { namespace imageTransforms
{
	CUVI_EXPORTS CuviStatus haarFwd(const CuviImage& src, CuviImage& dstApprox, CuviImage& dstDetailX, CuviImage& dstDetailY, CuviImage& dstDetailXY, const CuviStream& stream = CuviStream());
	
	CUVI_EXPORTS CuviStatus haarInv(const CuviImage& srcApprox, const CuviImage& srcDetailX, const CuviImage& srcDetailY, const CuviImage& srcDetailXY, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus fft2(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus fftShift(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus fftGetProperty(const CuviImage& src, CuviImage& dst, const CuviFFTProp prop, const CuviStream& stream = CuviStream());

}}

#endif
