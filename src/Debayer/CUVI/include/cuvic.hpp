#ifndef CUVIC_HPP
#define CUVIC_HPP

#ifndef __cplusplus
#error This Header Requires A C++ Compiler
#endif

#include "cuviCore.hpp"

namespace cuvi { namespace codecs
{

	CUVI_EXPORTS CuviStatus encode(const CuviImage& src, CuviImageFormat outputFormat, const std::string& outputPath, Cuvi32u quality = 70, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus encode(const CuviImage& src, CuviImageFormat outputFormat, Cuvi8u*& compressedData, Cuvi32u* compressedLength, Cuvi32u quality = 70, bool copyToCPU = true, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus decode(const Cuvi8u* src, const size_t srcBytes, CuviImage& dst, const bool srcOnGPU = false, const CuviStream& stream = CuviStream());

	CUVI_EXPORTS CuviStatus decode(const std::string& inputPath, CuviImage& dst, const CuviStream& stream = CuviStream());

}}

#endif
