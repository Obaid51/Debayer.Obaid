#ifndef AZUREBLOB_H
#define AZUREBLOB_H
#include "pthread.h"
#include "blob.h"
#include <filesystem>
#include "stdlib.h"

namespace fs = std::filesystem;
class AzureBlob
{
public:
    pthread_t mThread;
    pthread_mutex_t mMutex;
    pthread_cond_t mImageResived;
    static AzureBlob *startThread(std::string path_to_dir);
    void stopThread();
    std::atomic_bool needStop = false;
    std::string mPath;
};

void *AzureBlobThread(void*);
#endif // AZUREBLOB_H
