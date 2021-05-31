#ifndef image_BUFFER_H
#define image_BUFFER_H

#include <atomic>
#include <queue>
#include <string>
#include "RawImageProcessor/ImageStructs.h"

/**
 * @brief The mBuffer struct
 * @details contains pointer on queue of images(with meta) and counter of images, that shoud be deleted.
 */
struct ImageBuffer
{
    ImageBuffer()
    {
        pthread_cond_init(&image_was_processed,NULL);
        pthread_mutex_init(&image_was_processed_mutex,NULL);
        pthread_mutex_init(&image_processing_mutex,NULL);
        ImagesWithMeta = new std::queue<rawWithMeta>;
    };
    ~ImageBuffer()
    {
        pthread_cond_destroy(&image_was_processed);
        pthread_mutex_destroy(&image_was_processed_mutex);
        pthread_mutex_destroy(&image_processing_mutex);
        delete ImagesWithMeta;
    };
    std::queue<rawWithMeta> *ImagesWithMeta;                ///<! Struct, contains void* frame and meta for psqlDB
    std::atomic<int> frames_processed{ 0 };                 ///<! When frame is processed fully, this one will be incremented by Blob Thread;
    pthread_cond_t image_was_processed;
    pthread_mutex_t image_was_processed_mutex;
    pthread_mutex_t image_processing_mutex;
    pthread_mutex_t meta_processing_mutex;
};


#endif // BUFFER_H
