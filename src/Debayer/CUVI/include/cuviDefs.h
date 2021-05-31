/*
 * Copyright (C) 2010-2021 TunaCode Pvt. Ltd.  All rights reserved.
 *
 * NOTICE TO USER:   
 *
 * TUNACODE MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED
 * WARRANTY OF ANY KIND.  TUNACODE DISCLAIMS ALL WARRANTIES WITH REGARD TO
 * THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL 
 * TUNACODE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOURCE CODE.  
 *
 */




/*! \file include/cuviDefs.h
 *  \brief Contains types, data structures and enumerators used in CUVI
 *	Contains types, data structures and enumerators used in CUVI
 */

#ifndef CUVIDEFS_H
#define CUVIDEFS_H


#if ( defined _WIN32 || defined _WIN64 )
#define CUVI_EXPORTS __declspec(dllexport)
#elif defined __APPLE__
#define CUVI_EXPORTS
#elif defined __linux__
#define CUVI_EXPORTS __attribute__ ((visibility ("default")))

#endif
#ifdef _MSC_VER
#if _MSC_VER > 1500
#define CUVI_NULL nullptr
#else
#define CUVI_NULL NULL
#endif
#elif defined __linux__ || defined __APPLE__
#include<stdlib.h>
#if __cplusplus > 199711L
#define CUVI_NULL nullptr
#else
#define CUVI_NULL NULL
#endif
#endif

#if defined _WIN32 || defined WIN32
#define CUVI_INLINE	inline
#else
#define CUVI_INLINE
#endif




/************************************************************************************************************//**
* \brief This is the value of PI used across the library.
 ****************************************************************************************************************/
#define PI 3.141592653589793f


typedef signed char		Cuvi8s;		///< 8-bit signed char
typedef unsigned char   Cuvi8u;     ///< 8-bit unsigned char
typedef unsigned short  Cuvi16u;    ///< 16-bit unsigned short
typedef signed short    Cuvi16s;    ///< 16-bit signed short
typedef unsigned int    Cuvi32u;    ///< 32-bit unsigned integers
typedef signed int      Cuvi32s;    ///< 32-bit signed integers
typedef float           Cuvi32f;    ///< 32-bit (IEEE) floating-point numbers
typedef double          Cuvi64f;    ///< 64-bit floating-point numbers



#define	CUVI_DEPTH_8S -8
#define CUVI_DEPTH_8U 8
#define CUVI_DEPTH_16S -16
#define	CUVI_DEPTH_16U 16
#define	CUVI_DEPTH_32S -32
#define CUVI_DEPTH_32F 32
#define CUVI_DEPTH_64F 64


/**
 *\struct CuviPointPolar Structure used to store polar coordinates of a pixel
 */
template<typename T>
struct CUVI_EXPORTS CuviPointPolar 
{
    T   rho;	/**< Distance of Point From The Origin */
    T   theta;	/**< Angle of point with positive x axis */

	CuviPointPolar() : rho(0), theta(0){}
	CuviPointPolar(const T Rho, const T Theta) : rho(Rho), theta(Theta){}
	~CuviPointPolar(){rho=theta=0;}
};


/**
 *\struct CuviPoint2D Structure used to store coordinates of a pixel in 2D space
 */
template<typename T>
struct CUVI_EXPORTS CuviPoint2D
{
	T   x;	/**< x-coordinate of the point */
    T   y;	/**< y-coordinate of the point */

	CuviPoint2D() : x(0), y(0){}
	CuviPoint2D(const T x, const T y) : x(x), y(y){}
	~CuviPoint2D(){x=y=0;}
};


/**
 *\struct CuviPointValue2D Structure used to store coordinates and intensity value of a pixel in 2D space
 */
template<typename T1, typename T2>
struct CUVI_EXPORTS CuviPointValue2D
{
	T1 x;		/**< x-coordinate of the point */
	T1 y;		/**< y-coordinate of the point */
	T2 val;		/**< Pixel intensity value of the point */

	CuviPointValue2D() : x(0), y(0), val(0){}
	CuviPointValue2D(const T1 x, const T1 y, const T2 value) : x(x), y(y), val(value){}
	~CuviPointValue2D(){x=y=0;}
};

/**
 *\struct CuviPoint3D Structure used to store coordinates as well as value of a pixel in 3D space
 */
template<typename T>
struct CUVI_EXPORTS CuviPoint3D
{
	T   x;	/**< x-coordinate of the point */
 	T   y;	/**< y-coordinate of the point */
	T   z;	/**< z-coordinate of the point */

	CuviPoint3D():x(0),y(0),z(0){}
	CuviPoint3D(const T x,const T y,const T z):x(x),y(y),z(z){}
	~CuviPoint3D(){x=y=z=0;}
};




/**
 *\struct CuviRect Structure used to store the location and size of the region of interest
 */
struct CUVI_EXPORTS CuviRect
{
	Cuvi32s x;			/**< x-coordinate of the top left corner of region of interest */
	Cuvi32s y;			/**< y-coordinate of the top left corner of region of interest */
	Cuvi32s width;		/**< Width of the region of interest in pixels */
	Cuvi32s height;		/**< Height of the region of interest in pixels */

	CuviRect():x(0),y(0),width(0),height(0){}
	CuviRect(const Cuvi32s x, const Cuvi32s y, const Cuvi32s width, const Cuvi32s height):x(x),y(y),width(width),height(height){}
	~CuviRect(){x=y=width=height=0;}

	CuviPoint2D<int> origin() { return CuviPoint2D<int>(x, y); }
};


/**
 *\struct CuviSize Structure used to store width and height of an image
 */
struct CUVI_EXPORTS CuviSize
{
    Cuvi32s   width;		/**< Width of the image in pixels */
	Cuvi32s   height;		/**< Height of the image in pixels */

	CuviSize():width(0),height(0){}
	CuviSize(const Cuvi32s width, const Cuvi32s height):width(width),height(height){}
	~CuviSize(){width=height=0;}
};


class CUVI_EXPORTS CuviScalar
{
	Cuvi64f* _vals;
	bool _isInteger;
public:
	CuviScalar();
	CuviScalar(const CuviScalar&);
	CuviScalar(const Cuvi64f val);
	CuviScalar(const Cuvi32s val);
	CuviScalar(const Cuvi64f val1, const Cuvi64f val2, const Cuvi64f val3);
	CuviScalar(const Cuvi64f val1, const Cuvi64f val2, const Cuvi64f val3, const Cuvi64f val4);
	CuviScalar(const Cuvi32s val1, const Cuvi32s val2, const Cuvi32s val3);
	CuviScalar(const Cuvi32s val1, const Cuvi32s val2, const Cuvi32s val3, const Cuvi32s val4);
	~CuviScalar();

	bool isInteger() const;

	Cuvi64f* vals();
	const Cuvi64f* vals()		const;
	Cuvi64f& operator[](const int);
	const Cuvi64f& operator[](const int) const;
	
	CuviScalar operator-() const;
};

/**
\brief Type of mirroring specified to the function cuviFlipImage
*/
enum CuviFlipType
{
	CUVI_FLIP_UP_DOWN,				/**< Mirror the image vertically */
	CUVI_FLIP_LEFT_RIGHT,			/**< Mirror the image horizontally */
	CUVI_FLIP_BOTH_DIRECTIONS		/**< Mirror the image vertically as well as horizontally */
};

/**
\brief Point of rotation specified to the function cuviRotate
*/
enum  CuviRotationType
{
	CUVI_ROTATE_CENTER,			/**< Rotate the image from center */	
	CUVI_ROTATE_ORIGIN			/**< Rotate the image from origin */
};

/**
\brief Mode specifying the output size of rotated image
*/
enum CuviRotationMode
{
	CUVI_ROTATE_CROP,	/**< Output size same as input size */	
	CUVI_ROTATE_LOOSE	/**< Output contains the whole rotated image */	
};


enum CuviInterpolationType
{
	CUVI_INTER_NEAREST = 1,
	CUVI_INTER_LINEAR,
	CUVI_INTER_CUBIC

};


/**
\brief Type of derivative kernel used to compute gradients
*/
enum CuviGradientKernelType
{
	CUVI_GRADIENT_CENTRAL_DIFFERENCE,		/**< Central difference operator */

	CUVI_GRADIENT_SOBEL_3x3,				/**< 3 x 3 Sobel Operator */
	
	CUVI_GRADIENT_SCHARR_3x3,				/**< 3 x 3 Scharr Operator */
	
	CUVI_GRADIENT_PREWITT_3x3				/**< 3 x 3 Prewitt Operator */
};

/**
\brief Image feature selection algorithm
*/
enum CuviFeaturesAlgorithm
{
	CUVI_FEATURES_KLT,				/**< Kanade-Lucas-Tomasi feature selection */
	
	CUVI_FEATURES_HARRIS,			/**< Harris corner detector */

	CUVI_FEATURES_HARRIS_PETER		/**< Harris corner detector using Peter algorithm */
};

/**
\brief Image feature selection criteria
*/
struct CUVI_EXPORTS CuviFeaturesCriteria
{
	CuviFeaturesAlgorithm algorithm;		/**< Feature selection algorithm to use */
	Cuvi32f featureQuality;					/**< Minimum Quality of a feature relative to the best feature of the image. Features below this quality level are discarded */
	Cuvi32s minimumDistance;				/**< Minimum distance in pixels between two features */
	Cuvi32s blockSize;						/**< Windows size used to compute eigen values of the image */
	Cuvi32f k;								/**< Harris corner detector parameter. Works only if the algorithm is CUVI_FEATURES_HARRIS */

	CuviFeaturesCriteria(const CuviFeaturesAlgorithm algo = CUVI_FEATURES_KLT, const Cuvi32f featureQuality = 0.006f, const Cuvi32s minDistance = 5, const Cuvi32s blockSize = 3, const Cuvi32f k = -0.2f);
	~CuviFeaturesCriteria();
};

/**
\struct CuviTrackingCriteria
\brief Image feature tracking criteria
*/
struct CUVI_EXPORTS CuviTrackingCriteria
{
	Cuvi32s pyramidLevels;		/**< Number of pyramidal images created besides original image */
	CuviSize windowSize;		/**< Tracking window size */
	Cuvi32s iterations;			/**< Maximum number of iterations to track a feature until the tracked location converges to an image coordinate */
	Cuvi32f maxResidue;			/**< Threshold for absolute difference between initial point and tracked point. If the sum of absolute difference of tracking window between the two locations is less than or equal to this value, the feature is declared as tracked. */
	Cuvi32f errorThreshold;		/**< Threshold for tracking convergence */
	Cuvi32f subSampling;		/**< The scaling level used to create pyramidal images */

	CuviTrackingCriteria(const Cuvi32s pyramidLevels = 3, const CuviSize& windowSize = CuviSize(3,3), const Cuvi32s iterations = 10, const Cuvi32f residue = 20.0f, const Cuvi32f errorThreshold = 0.01f, const Cuvi32f subSampling = 0.5f);
	~CuviTrackingCriteria();
};



struct CUVI_EXPORTS CuviEnhancementParams
{
	bool autoColor;
	Cuvi32u filterStrength;
	Cuvi64f deGalreAmount;
	/*
	Cuvi32s contrastPower;
	Cuvi32s contrastMetric;
	CuviSize smoothingWindowSize;
	Cuvi32f smoothingWindowSigma;
	CuviSize medianWindowSize;

	Cuvi32f exposednessMean;
	Cuvi32f exposednessVariance;
	Cuvi32f scaleFactor;
	*/

	CuviEnhancementParams(bool autoColor = true, Cuvi32u filterStrength = 2, Cuvi64f deGalreAmount = 0.1333/* ,Cuvi32s power = 6, Cuvi32s metric = 0, CuviSize smoothWindowSize = CuviSize(7, 7), Cuvi32f smoothSigma = 7.0f, CuviSize medianWindowSize = CuviSize(3, 3), Cuvi32f emean = 0.5f, Cuvi32f evariance = 0.25f, Cuvi32f scale = 1.0f*/);
	~CuviEnhancementParams();
};

enum CuviStatus
{
	CUVI_NO_ERROR = 0,
	CUVI_SUCCESS = CUVI_NO_ERROR,            

	CUVI_MEM_ALLOC_ERR = -1,
	CUVI_ARRAY_ALLOC_ERR = -2,
	CUVI_MEMSET_ERR = -3,
	CUVI_MEMCPY_H2D_ERROR = -4,
	CUVI_MEMCPY_D2H_ERROR = -5,
	CUVI_MEMCPY_D2D_ERROR = -6,
	CUVI_MEMCPY_D2A_ERROR = -7,
	CUVI_MEMCPY_H2S_ERROR = -8,
	CUVI_MEMCPY_ERROR = -9,
	CUVI_MEMFREE_ERR = -10,
	CUVI_MEMFREE_ARRAY_ERR = -11,

	CUVI_TEXTURE_BIND_ERROR = -12,
	CUVI_TEXTURE_UNBIND_ERROR = -13,

	CUVI_IMAGE_NOT_INITIALIZED = -14,
	CUVI_NULL_POINTER_ERROR = -15,
	CUVI_INVALID_ARG_ERROR = -16,
	CUVI_NOT_SUPPORTED_MODE_ERROR = -17,


	CUVI_SIZE_ERROR = -18,
	CUVI_INVALID_ROI_ERROR = -19,

	CUVI_CUDA_KERNEL_EXECUTION_ERROR = -20,
	CUVI_INTERNAL_FUNCTION_CALL_ERROR = -21,
	CUVI_INTERNAL_CALL_ERROR = -22,


	CUVI_CHANNEL_NOT_SUPPORTED_ERROR = -23,
	CUVI_TRIAL_VERSION_LIMIT_ERROR = -24,
	CUVI_DEPTH_NOT_SUPPORTED_ERROR = -25,
	CUVI_MEMORY_PINNING_ERROR = -26,
	CUVI_MEMORY_UNPINNING_ERROR = -27,
	CUVI_STREAM_CREATE_ERROR = -28,
	CUVI_STREAM_DESTROY_ERROR = -29,

	CUVI_OPENCL_ERROR = -30,

	CUVI_DIFFERENT_IMAGE_SIZE_ERROR = -31,
	CUVI_DEVICE_NOT_FOUND_ERROR = -32,
	CUVI_INVALID_DEVICE_ERROR = -33,
	CUVI_DRIVER_NOT_FOUND_ERROR = -34,
	CUVI_DRIVER_NOT_SUPPORTED_ERROR = -35,
	CUVI_UNKNOWN_ERROR = -36,
	CUVI_TYPE_NOT_SUPPORTED_ERROR = -37,
	CUVI_INPLACE_OP_NOT_SUPPORTED = -38,
	CUVI_SINGULAR_MATRIX_ERROR = -39,

	CUVI_JPEG_PARAM_ERROR = -40,
	CUVI_JPEG_ENCODE_ERROR = -41,
	CUVI_JPEG_DECODE_ERROR = -42,
	
	CUVI_WARP_AFFINE_INCORRECT_QUAD_WARNING = 1
};

enum CuviType
{
	CUVI_8UC1, CUVI_8UC2, CUVI_8UC3, CUVI_8UC4,
	CUVI_8SC1, CUVI_8SC2, CUVI_8SC3, CUVI_8SC4,
	CUVI_16UC1, CUVI_16UC2, CUVI_16UC3, CUVI_16UC4,
	CUVI_16SC1, CUVI_16SC2, CUVI_16SC3, CUVI_16SC4,
	CUVI_32FC1, CUVI_32FC2, CUVI_32FC3, CUVI_32FC4,
	CUVI_32SC1, CUVI_32SC2, CUVI_32SC3, CUVI_32SC4,
	CUVI_64FC1, CUVI_64FC2, CUVI_64FC3, CUVI_64FC4,
	CUVI_COMPLEX32 = CUVI_32FC2,
	CUVI_COMPLEX64 = CUVI_64FC2,
	CUVI_NO_TYPE = -1,
	CUVI_UNKNOWN_TYPE = -2
};


/**
\brief Sequence of pixel values placement in the image
*/
enum CuviChannelSeq
{
	CUVI_CHANNEL_SEQ_RGB,		/**< Pixels are placed as | RED | GREEN | BLUE | RED | GREEN | BLUE |... */	
	CUVI_CHANNEL_SEQ_BGR,		/**< Pixels are placed as | BLUE | GREEN | RED | BLUE | GREEN | RED |... */	
	CUVI_CHANNEL_SEQ_BGRA,		/**< Pixels are placed as | BLUE | GREEN | RED | ALPHA | BLUE | GREEN | RED | ALPHA |... */	
	CUVI_CHANNEL_SEQ_RGBA,		/**< Pixels are placed as | RED | GREEN | BLUE | ALPHA | RED | GREEN | BLUE | ALPHA |... */	
	CUVI_CHANNEL_SEQ_LUMINANCE,	/**< Single channel image */
	CUVI_CHANNEL_SEQ_NONE
};

enum CuviImageFormat
{
	CUVI_JPEG = 0,
};


/**
\brief Sequence of color sensors in the Bayer image
*/
enum CuviBayerSeq
{
	CUVI_BAYER_BLANK, //default argument, for error-checking
	

	CUVI_BAYER_BGGR,	/**< 
						Sensors are placed in the order
						| B | G |
						| G | R | 
						
						*/
	
	CUVI_BAYER_GBRG,	/**< 
						Sensors are placed in the order
						| G | B |
						| R | G |
						
						*/
	
	CUVI_BAYER_GRBG,	/**< 
						Sensors are placed in the order
						| G | R |
						| B | G |
						
						*/
	
	CUVI_BAYER_RGGB,	/**< 
						Sensors are placed in the order
						| R | G |
						| G | B |
						
						*/
	
	CUVI_BAYER_BGGR_HQ,	/**< 
						Sensors are placed in the order
						| B | G |
						| G | R |
						Use high quality interpolation mode
						
						*/
	
	CUVI_BAYER_GRBG_HQ,	/**< 
						Sensors are placed in the order
						| G | R |
						| B | G |
						Use high quality interpolation mode
						
						*/
	
	CUVI_BAYER_RGGB_HQ,	/**< 
						Sensors are placed in the order
						| R | G |
						| G | B |
						Use high quality interpolation mode
						
						*/
	
	CUVI_BAYER_GBRG_HQ	/**< 
						Sensors are placed in the order
						| G | B |
						| R | G |
						Use high quality interpolation mode
						
						*/

};

/**
\brief Predefined Colors
*/
enum CuviColor
{
	CUVI_COLOR_RED,
	CUVI_COLOR_GREEN,
	CUVI_COLOR_BLUE
};

enum CuviLoadType
{
	CUVI_LOAD_IMAGE_DEFAULT = -1,			/**< Load Image As Is */
	CUVI_LOAD_IMAGE_GRAYSCALE,				/**< Load image as 8 bit gray scale */
	CUVI_LOAD_IMAGE_COLOR,					/**< Load image as 8 bit */
	CUVI_LOAD_IMAGE_GRAYSCALE_KEEP_DEPTH,	/**< Load image as gray scale, with original depth */
	CUVI_LOAD_IMAGE_COLOR_KEEP_DEPTH		/**< Load image with original depth */
};

/**
\brief FFT Property to get from complex fft output
*/
enum CuviFFTProp
{
	CUVI_FFT_MAGNITUDE = 0,			/**< Magnitude of fft */
	CUVI_FFT_SCALED_MAGNITUDE = 1,	/**< Magnitude of fft divided by number of rows */
	CUVI_FFT_PHASE = 2,				/**< Phase of fft */
	CUVI_FFT_SCALED_PHASE =  3,		/**< Phase of fft divided by number of rows */
	CUVI_FFT_REAL = 4,				/**< Real part of fft */
	CUVI_FFT_SCALED_REAL = 5,		/**< Real part of fft divided by number of rows */
	CUVI_FFT_IMAGINARY = 6,			/**< Imaginary part of fft */
	CUVI_FFT_SCALED_IMAGINARY = 7	/**< Imaginary part of fft divided by number of rows */
};


enum CuviPointerType
{
	CUVI_PTR_NONE = -1,
	CUVI_PTR_DEVICE,
	CUVI_PTR_HOST,
	CUVI_PTR_HOST_PAGE_LOCKED,
	//CUVI_PTR_HOST_MAPPED,
	//CUVI_PTR_HOST_PORTABLE,
};


/**
\brief The class used for storing a filter kernel
*/
class CUVI_EXPORTS CuviFilter
{
	Cuvi32s _width;			/**< Width of the filter */	
	Cuvi32s _height;		/**< Height of the filter */	
	Cuvi32f* _coeffs;		/**< Taps of the filter */	
	CuviPoint2D<Cuvi32s> _anchor;
	bool _init;

public:

	bool create(const CuviSize& size);
	bool create(const CuviSize& size, Cuvi32f* coeffs);
	bool create(const CuviSize& size, const CuviPoint2D<int>& anchor);
	bool create(const CuviSize& size, const CuviPoint2D<int>& anchor, Cuvi32f* coeffs);
	bool create(const int width, const int height);
	bool create(const int width, const int height, Cuvi32f* coeffs);
	bool create(const Cuvi32s width, const Cuvi32s height, const CuviPoint2D<int>& anchor);
	bool create(const Cuvi32s width, const Cuvi32s height, const CuviPoint2D<int>& anchor, Cuvi32f* coeffs);
	bool release();

	CuviFilter();
	CuviFilter(const Cuvi32s width, const Cuvi32s height);
	CuviFilter(const Cuvi32s width, const Cuvi32s height, Cuvi32f* coeffs);
	CuviFilter(const Cuvi32s width, const Cuvi32s height, const CuviPoint2D<int>& anchor);
	CuviFilter(const Cuvi32s width, const Cuvi32s height, const CuviPoint2D<int>& anchor, Cuvi32f* coeffs);
	CuviFilter(const CuviSize& size);
	CuviFilter(const CuviSize& size, Cuvi32f* coeffs);
	CuviFilter(const CuviSize& size, const CuviPoint2D<int>& anchor);
	CuviFilter(const CuviSize& size, const CuviPoint2D<int>& anchor, Cuvi32f* coeffs);

	bool isInitialized() const;

	Cuvi32s width()					const;
	Cuvi32s height()				const;
	Cuvi32f* coeffs()				const;
	CuviPoint2D<Cuvi32s> anchor()	const;

	Cuvi32f& operator[](int i);
	const Cuvi32f& operator[](int i) const;
	Cuvi32f& operator()(int i, int j);
	const Cuvi32f& operator()(int i, int j) const;
	~CuviFilter();
};

/**
\brief CuviStream for asynchronous operations
*/
class CUVI_EXPORTS CuviStream
{
	void* _stream;	/**< Actual CUDA stream encapsulated by CUVI Stream */
	bool _init;
	bool _isDefault;
	Cuvi32s _id;
public:
	CuviStream(bool newStream = false);
	void* ptr() const;
	void create();
	void destroy();
	void sync() const;
	bool finished() const;
	bool isDefault() const;
	Cuvi32s id() const;
	~CuviStream();
};

class CUVI_EXPORTS CuviSpecialFilters
{
public:
	static CuviFilter average(const CuviSize& size);
	static CuviFilter sobel();
	static CuviFilter scharr();
	static CuviFilter prewitt();
	static CuviFilter gaussian(const CuviSize& size = CuviSize(3,3), Cuvi32f sigma = 0.5f);
	static CuviFilter laplacian(Cuvi32f alpha = 0.2f);
	static CuviFilter unsharp(Cuvi32f alpha = 0.2f);
};

/**
\brief struct CuviDeviceProperties to hold the CUDA device information
*/
struct CuviDeviceProperties
{
	char deviceName[256];		/**< ASCII string identifying device */
	int smCount;				/**< Number of streaming multiprocessors on the device*/
	int coresPerSM;				/**< Number of cores per multiprocessor */
	int totalCoreCount;			/**< Number of cores of the device */
	Cuvi32f computeCapability;	/**< Compute Capability of CUDA Device*/
	int asyncEngineCount;		/**< Specifies if the device can overlap memory copies with kernel execution */
	size_t globalMemory;		/**< Total Global Memory Of The Device In Bytes */
	size_t freeGlobalMemory;	/**< Available Global Memory Of The Device In Bytes */
	size_t constantMemory;		/**< Total Constant Memory Of The Device In Bytes */
	int textureAlignment;		/**< Texture Alignment In Bytes */
	int clockRate;				/**< Clock Rate of Device in KiloHertz */
};

#endif
