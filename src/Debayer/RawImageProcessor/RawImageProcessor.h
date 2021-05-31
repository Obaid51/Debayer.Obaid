// RawImageProcessor.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <time.h>
//#include "pnm.h"
//#include <opencv2/cv.hpp>
#include "pthread.h"
#include <deque>
#include <proto/FileStream.grpc.pb.h>
#include <proto/FileStream.pb.h>
#include <gRPC/buffer.h>
#include "CUVI/CuviPipeline.h"
#define NUM_BUFFERS 16
#include "Blob/azureblob.h"
#include <iostream>

struct rawWithMeta;

struct ThreadStruct

{
  ThreadStruct()
  {
    isStarted = false;
    needStop.store(false,std::memory_order_relaxed);
  }
  pthread_t mProcessingThread;
  bool isStarted;
  std::atomic_bool needStop;
};


class RawImageProcessor
{
    //std::deque<rawWithMeta> dequeOfImgs;
    pthread_mutex_t deque_mtx;
    pthread_mutex_t buffer_mtx;
    pthread_mutex_t data_mtx;
    pthread_mutex_t meta_mtx;

    size_t image_size;
public:
    AzureBlob *blob;
    ThreadStruct mThreadStruct;
    ImageBuffer *image_buffer;
    RawImageProcessor();
    ~RawImageProcessor();
    bool start(ImageBuffer*);
    bool stop();
};


void* rawThread(void*);

// TODO: Reference additional headers your program requires here.
