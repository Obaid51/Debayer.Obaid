#ifndef CUVI_IO_HPP
#define CUVI_IO_HPP

#ifndef __cplusplus
#error This Header Requires A C++ Compiler
#endif

#include "cuviCore.hpp"

namespace cuvi {
	namespace io
	{
		CUVI_EXPORTS CuviImage loadImage(const std::string& path, const CuviLoadType type = CUVI_LOAD_IMAGE_COLOR);

		CUVI_EXPORTS CuviStatus saveImage(CuviImage& image, const std::string& path);

		typedef struct _CuviVideoReaderImpl* CuviVideoReaderImpl;

		class CUVI_EXPORTS CuviVideoReader
		{
			CuviVideoReaderImpl impl;

		public:
			CuviVideoReader();
			CuviVideoReader(const std::string& path);
			CuviVideoReader(Cuvi32s cameraID);

			bool open(const std::string& path);
			bool open(Cuvi32s cameraID);

			bool isInitialized() const;

			Cuvi32s width() const;
			Cuvi32s height() const;
			Cuvi64f fps() const;
			Cuvi32s numFrames() const;

			CuviStatus nextFrame(CuviImage& frame);
			CuviStatus operator>>(CuviImage&);

			void release();

			~CuviVideoReader();
		};
	}
}


namespace cuvi
{
	CUVI_EXPORTS CuviStatus createWindow(const std::string& title, bool resizable = false);
	CUVI_EXPORTS CuviStatus showImage(const std::string& title, const CuviImage& image);
	CUVI_EXPORTS Cuvi32s waitKeyPress(Cuvi32s ms = 0);
}

#endif