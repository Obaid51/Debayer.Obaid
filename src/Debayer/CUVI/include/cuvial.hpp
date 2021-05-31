#ifndef CUVIAL_HPP
#define CUVIAL_HPP

#ifndef __cplusplus
#error This Header Requires A C++ Compiler
#endif


#include "cuviCore.hpp"

namespace cuvi { namespace arithmeticLogical
{
	CUVI_EXPORTS CuviStatus add(const CuviImage& src1, const CuviImage& src2, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus add(const CuviImage& src, const Cuvi64f value, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus add(const CuviImage& src, const CuviScalar& values, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus subtract(const CuviImage& src1, const CuviImage& src2, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus subtract(const Cuvi64f value, const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus subtract(const CuviScalar& values, const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus multiply(const CuviImage& src1, const CuviImage& src2, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus multiply(const CuviImage& src, const Cuvi64f value, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus multiply(const CuviImage& src, const CuviScalar& values, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus divide(const CuviImage& src1, const CuviImage& src2, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus divide(const Cuvi64f value, const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus divide(const CuviScalar& values, const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());
	
	CUVI_EXPORTS CuviStatus pow(const CuviImage& src, const Cuvi64f power, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus exp(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus abs(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus absDiff(const CuviImage& src1, const CuviImage& src2, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus sqrt(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus cbrt(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus floor(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus ceil(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus round(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus AND(const CuviImage& src1, const CuviImage& src2, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus AND(const CuviImage& src, const Cuvi32s value, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus OR(const CuviImage& src1, const CuviImage& src2, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus OR(const CuviImage& src, const Cuvi32s value, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus XOR(const CuviImage& src1, const CuviImage& src2, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus XOR(const CuviImage& src, const Cuvi32s value, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus NOT(const CuviImage& src, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus SHL(const CuviImage& src, const Cuvi32s value, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus SHR(const CuviImage& src, const Cuvi32s value, CuviImage& dst, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus matMul(const CuviImage& A, const CuviImage& B, CuviImage& C, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus matMulTrans(const CuviImage& A, CuviImage& B, bool trans = false, const CuviStream& stream = CuviStream());

}}

#endif
