#ifndef CUVI_CORE_HPP
#define CUVI_CORE_HPP

#ifndef __cplusplus
#error This Header Requires A C++ Compiler
#endif

#include "cuviDefs.h"

#if defined __linux__
#include <sys/time.h> //For timeval structure
#endif

#if defined __APPLE__
#include <sys/time.h>
#endif

#include<string>

/**
 *\class CuviImage to hold image information on the device
 */
class CUVI_EXPORTS CuviImage
{
	bool _init;					/**< Specifies if the image has been created successfully or not */
	bool _signed;				/**< true if the image also contains negative values. false in case of floating point or unsigned types */
	
	void* _data;						/**< Device pointer of the actual image data */
	Cuvi32s _width;						/**< Width of the image in pixels */
	Cuvi32s _height;					/**< Height of the image in pixels */
	Cuvi32s _pitch;						/**< Width of the image in bytes. Also referred as stride or widthStep */
	Cuvi32s _depth;						/**< Bit depth of the image */
	Cuvi32s _channels;					/**< Number of channels of the image */
	Cuvi32s _dataBits;					/**< Actual data bits of the image */
	CuviChannelSeq _channelSequence;	/**< Channel sequence of the image */
	CuviType _type;
	
public:

	CuviStatus create(const Cuvi32s width, const Cuvi32s height, const Cuvi32s depth, const Cuvi32s channels);
	CuviStatus create(const Cuvi32s width, const Cuvi32s height, const Cuvi32s pitch, const Cuvi32s depth, const Cuvi32s channels);
	CuviStatus create(const CuviSize& size, const Cuvi32s depth, const Cuvi32s channels);
	CuviStatus create(const Cuvi32s width, const Cuvi32s height, const CuviType type);
	CuviStatus create(const CuviSize& size, const CuviType type);
	CuviStatus create(const std::string& path, const CuviLoadType type = CUVI_LOAD_IMAGE_COLOR);

	CuviStatus release();

	Cuvi32s width()					const;
	Cuvi32s height()				const;
	CuviSize size()					const;
	Cuvi32s pitch()					const;
	Cuvi32s	depth()					const;
	Cuvi32s channels()				const;
	Cuvi32s dataBits()				const;
	CuviType type()					const;
	CuviChannelSeq channelSeq()		const;
	bool isSigned()					const;
	bool isInitialized()			const;

	CuviStatus setDataBits(const Cuvi32s dataBits);
	void setChannelSequence(const CuviChannelSeq sequence);

	void* ptr() const;
	template<typename T> T* ptr() const {return reinterpret_cast<T*>(_data);}

	CuviScalar get(const Cuvi32s x, const Cuvi32s y) const;
	Cuvi64f get(const Cuvi32s x, const Cuvi32s y, const Cuvi32s channel) const;

	CuviStatus set(const Cuvi32s x, const Cuvi32s y, const CuviScalar& value);
	CuviStatus set(const Cuvi32s x, const Cuvi32s y, const Cuvi32s channel, const Cuvi64f value);

	CuviStatus set(const Cuvi64f value, const CuviStream& stream = CuviStream());
	CuviStatus set(const CuviScalar& values, const CuviStream& stream = CuviStream());
	CuviStatus set(const Cuvi32s channel, const Cuvi64f value, const CuviStream& stream = CuviStream());

	CuviImage();
	CuviImage(const Cuvi32s width, const Cuvi32s height, const Cuvi32s depth, const Cuvi32s channels);
	CuviImage(const Cuvi32s width, const Cuvi32s height, const Cuvi32s pitch, const Cuvi32s depth, const Cuvi32s channels);
	CuviImage(const CuviSize& size, const Cuvi32s depth, const Cuvi32s channels);
	CuviImage(const Cuvi32s width, const Cuvi32s height, const CuviType type);
	CuviImage(const CuviSize& size, const CuviType type);
	CuviImage(const std::string& path, const CuviLoadType type = CUVI_LOAD_IMAGE_COLOR);

	CuviImage(const CuviImage& rhs);
	CuviImage& operator=(const CuviImage& rhs);
	~CuviImage();
	
	static const CuviImage null();

	/* Channel fetch operator */
	CuviImage operator[](Cuvi32s);

	CuviStatus upload(const void* pSrcHost, const Cuvi32s srcPitch);
	CuviStatus upload(const void* pSrcHost, const Cuvi32s srcPitch, const CuviStream& stream);

	CuviStatus upload(const void* pSrcHost, CuviRect srcROI, const Cuvi32s srcPitch, CuviPoint2D<int> dstOrigin);
	CuviStatus upload(const void* pSrcHost, CuviRect srcROI, const Cuvi32s srcPitch, CuviPoint2D<int> dstOrigin, const CuviStream& stream);

	CuviStatus upload(const void* pSrcHost);
	CuviStatus upload(const void* pSrcHost, const CuviStream& stream);

	

	CuviStatus download(void* pDstHost, const Cuvi32s dstPitch)	const;
	CuviStatus download(void* pDstHost, const Cuvi32s dstPitch, const CuviStream& stream)	const;

	CuviStatus download(void* pDstHost, CuviPoint2D<int> dstOrigin, const Cuvi32s dstPitch, CuviRect srcROI);
	CuviStatus download(void* pDstHost, CuviPoint2D<int> dstOrigin, const Cuvi32s dstPitch, CuviRect srcROI, const CuviStream& stream);

	CuviStatus download(void* pDstHost) const;
	CuviStatus download(void* pDstHost, const CuviStream& stream) const;
	CuviStatus show(const std::string& title = "CUVI Image",Cuvi32s milliseconds = 0) const;

	CuviStatus convertTo(CuviImage& dst, const CuviType type, const Cuvi32f scale = 1.0f, const Cuvi32f offset = 0.0f, const CuviStream& stream = CuviStream());
	CuviStatus convertTo(CuviImage& dst, const Cuvi32s depth, const Cuvi32f scale = 1.0f, const Cuvi32f offset = 0.0f, const CuviStream& stream = CuviStream());

	CuviStatus copyTo(CuviImage& dst, CuviPoint2D<int> dstOrigin, CuviRect srcROI, const CuviStream& stream = CuviStream()) const;

	CuviImage operator-() const;

	CuviImage& operator++(); //Pre
	CuviImage operator++(Cuvi32s); //Post
	
	CuviImage& operator--(); //Pre
	CuviImage operator--(Cuvi32s); //Post

	CuviImage& operator+=(const CuviImage&);
	CuviImage& operator+=(Cuvi32s);
	CuviImage& operator+=(Cuvi64f);
	CuviImage& operator+=(const CuviScalar&);

	CuviImage& operator-=(const CuviImage&);
	CuviImage& operator-=(Cuvi32s);
	CuviImage& operator-=(Cuvi64f);
	CuviImage& operator-=(const CuviScalar&);

	CuviImage& operator*=(const CuviImage&);
	CuviImage& operator*=(Cuvi32s);
	CuviImage& operator*=(Cuvi64f);
	CuviImage& operator*=(const CuviScalar&);

	CuviImage& operator/=(const CuviImage&);
	CuviImage& operator/=(Cuvi32s);
	CuviImage& operator/=(Cuvi64f);
	CuviImage& operator/=(const CuviScalar&);

	CuviImage& operator&=(const CuviImage&);
	CuviImage& operator&=(Cuvi32s);

	CuviImage& operator|=(const CuviImage&);
	CuviImage& operator|=(Cuvi32s);

	CuviImage& operator^=(const CuviImage&);
	CuviImage& operator^=(Cuvi32s);

	CuviImage& operator<<=(Cuvi32s);

	CuviImage& operator>>=(Cuvi32s);
};


CUVI_EXPORTS CuviImage operator+(const CuviImage&, const CuviImage&);
CUVI_EXPORTS CuviImage operator+(Cuvi32s, const CuviImage&);
CUVI_EXPORTS CuviImage operator+(Cuvi64f, const CuviImage&);
CUVI_EXPORTS CuviImage operator+(const CuviImage&, Cuvi32s);
CUVI_EXPORTS CuviImage operator+(const CuviImage&, Cuvi64f);
CUVI_EXPORTS CuviImage operator+(const CuviImage&, const CuviScalar&);
CUVI_EXPORTS CuviImage operator+(const CuviScalar&, const CuviImage&);

CUVI_EXPORTS CuviImage operator-(const CuviImage&, const CuviImage&);
CUVI_EXPORTS CuviImage operator-(Cuvi32s, const CuviImage&);
CUVI_EXPORTS CuviImage operator-(Cuvi64f, const CuviImage&);
CUVI_EXPORTS CuviImage operator-(const CuviImage&, Cuvi32s);
CUVI_EXPORTS CuviImage operator-(const CuviImage&, Cuvi64f);
CUVI_EXPORTS CuviImage operator-(const CuviImage&, const CuviScalar&);
CUVI_EXPORTS CuviImage operator-(const CuviScalar&, const CuviImage&);

CUVI_EXPORTS CuviImage operator*(const CuviImage&, const CuviImage&);
CUVI_EXPORTS CuviImage operator*(Cuvi32s, const CuviImage&);
CUVI_EXPORTS CuviImage operator*(Cuvi64f, const CuviImage&);
CUVI_EXPORTS CuviImage operator*(const CuviImage&, Cuvi32s);
CUVI_EXPORTS CuviImage operator*(const CuviImage&, Cuvi64f);
CUVI_EXPORTS CuviImage operator*(const CuviImage&, const CuviScalar&);
CUVI_EXPORTS CuviImage operator*(const CuviScalar&, const CuviImage&);

CUVI_EXPORTS CuviImage operator/(const CuviImage&, const CuviImage&);
CUVI_EXPORTS CuviImage operator/(Cuvi32s, const CuviImage&);
CUVI_EXPORTS CuviImage operator/(Cuvi64f, const CuviImage&);
CUVI_EXPORTS CuviImage operator/(const CuviImage&, Cuvi32s);
CUVI_EXPORTS CuviImage operator/(const CuviImage&, Cuvi64f);
CUVI_EXPORTS CuviImage operator/(const CuviImage&, const CuviScalar&);
CUVI_EXPORTS CuviImage operator/(const CuviScalar&, const CuviImage&);

CUVI_EXPORTS CuviImage operator&(const CuviImage&, const CuviImage&);
CUVI_EXPORTS CuviImage operator&(const CuviImage&, Cuvi32s);
CUVI_EXPORTS CuviImage operator&(Cuvi32s, const CuviImage&);

CUVI_EXPORTS CuviImage operator|(const CuviImage&, const CuviImage&);
CUVI_EXPORTS CuviImage operator|(const CuviImage&, Cuvi32s);
CUVI_EXPORTS CuviImage operator|(Cuvi32s, const CuviImage&);

CUVI_EXPORTS CuviImage operator^(const CuviImage&, const CuviImage&);
CUVI_EXPORTS CuviImage operator^(const CuviImage&, Cuvi32s);
CUVI_EXPORTS CuviImage operator^(Cuvi32s, const CuviImage&);

CUVI_EXPORTS CuviImage operator~(const CuviImage&);

CUVI_EXPORTS CuviImage operator<<(const CuviImage&, Cuvi32s);

CUVI_EXPORTS CuviImage operator>>(const CuviImage&, Cuvi32s);



class CUVI_EXPORTS CuviPyramid
{
	void* _pyramid;
	Cuvi32s _levels;
	bool _init;
	Cuvi32f _scale;

public:

	CuviPyramid();
	CuviPyramid(const CuviImage& image, const Cuvi32s levels, const Cuvi32f scale = 0.5f, CuviInterpolationType inter = CUVI_INTER_LINEAR);
	CuviPyramid(const CuviSize& size, const CuviType type, const Cuvi32s levels, const Cuvi32f scale = 0.5f);

	bool isInitialized() const;
	Cuvi32s levels() const;
	Cuvi32f scale() const;

	const CuviImage& largest() const;
	const CuviImage& smallest() const;

	CuviStatus create(const CuviSize& size, const CuviType type, const Cuvi32s levels, const Cuvi32f scale = 0.5f);
	CuviStatus create(const CuviImage& image, const Cuvi32s levels, const Cuvi32f scale = 0.5f, CuviInterpolationType inter = CUVI_INTER_LINEAR);
	
	CuviStatus createGaussian(const CuviImage& image, const Cuvi32s levels, const Cuvi32f scale = 0.5f, const CuviSize& filterSize = CuviSize(5,5), const Cuvi32f sigma = 0.5f, CuviInterpolationType inter = CUVI_INTER_LINEAR);
	CuviStatus createLaplacian(const CuviImage& image, const Cuvi32s levels, const Cuvi32f scale = 0.5f, const CuviSize& filterSize = CuviSize(5,5), const Cuvi32f sigma = 0.5f, CuviInterpolationType inter = CUVI_INTER_LINEAR);
	
	CuviStatus release();

	CuviImage& operator[](Cuvi32s);
	const CuviImage& operator[](Cuvi32s) const;

	~CuviPyramid();
};


class CUVI_EXPORTS CuviHistogram
{
	bool _init;
	Cuvi32u* _hist;
	Cuvi32s _bins;
	CuviType _type;
	CuviPointerType _loc;

public:
	CuviHistogram();
	CuviHistogram(const Cuvi32s bins, CuviPointerType location = CUVI_PTR_HOST);
	CuviHistogram(const CuviType type, CuviPointerType location = CUVI_PTR_HOST);

	CuviStatus create(const Cuvi32s bins, CuviPointerType location = CUVI_PTR_HOST);
	CuviStatus create(const CuviType type, CuviPointerType location = CUVI_PTR_HOST);

	bool isInitialized() const;

	Cuvi32u* hist();
	const Cuvi32u* hist() const;
	Cuvi32s binCount() const;
	CuviType type() const;
	CuviPointerType location() const;

	CuviStatus release();

	~CuviHistogram();
};


class CUVI_EXPORTS CuviTimer 
{
#if defined _WIN32 || defined _WIN64
	__int64 _freq;
	__int64 _clocks;
	__int64 _start;
#elif defined __linux__
	timeval startTime;
	timeval endTime;
#else
	timeval startTime;
	timeval endTime;
	//Add MAC OS X Code Here
#endif

public:
	CuviTimer();   
	~CuviTimer();
	void Start(void);
	void Stop(void);
	void Reset(void);
	Cuvi64f GetElapsedTime(void);
};

#endif