#ifndef IMAGESTRUCTS_H
#define IMAGESTRUCTS_H
#include <boost/uuid/uuid.hpp>
#include <string>
#include <time.h>

enum imageFormat{
    raw,
    jpg,
    heifi
};

struct imageMetaInfo
{
    boost::uuids::uuid imageId;    //generating in UUID thread
    std::string imageName;         // ?? Need to ask
    std::string storageLink;       // Some info from Azure?
    int rawFrameId;               // Recieving from gRPC
    std::string mRawHash;           // Genereating in gRPC
    time_t mCaptureTimeStamp;       // Recieveing from gRPC
    std::string cameraId;          // Recieveing from gRPC
    std::string lensId;            // Recieveing from gRPC
    imageFormat mImageFormat;       // .. Maybe will need later
};

struct rawWithMeta
{
    rawWithMeta(void* img,imageMetaInfo meta)
    {
        imgFromgRPC = img;
        mMeta = meta;
    };
    void *imgFromgRPC;               // void* pointer to string, contains image
    imageMetaInfo mMeta;
};

#endif // IMAGESTRUCTS_H
