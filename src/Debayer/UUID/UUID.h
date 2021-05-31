#include <iostream>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <queue>
#include "../RawImageProcessor/ImageStructs.h"
#include "../psqlDebayer/psqlDebayer.h"
#include <gRPC/buffer.h>

class mUUIDv5
{

public:
    std::queue <imageMetaInfo> queImages;
    //boost::uuids::basic_random_generator<boost::mt19937> gen;
    pthread_cond_t sended_uuid_cond;


    pthread_mutex_t que_mtx;
    pthread_mutex_t sended_uuid_mtx;
    pthread_mutex_t started_mutex;

//    pthread_cond_t thread_started_cond;

    static mUUIDv5* createThread(ImageBuffer*);
    boost::uuids::uuid RAW_namespace ;
    boost::uuids::uuid JPEG_namespace;
    boost::uuids::uuid HEIF_namespace;

    boost::uuids::uuid RawImageUUID;
    boost::uuids::uuid JpegImageUUID;
    boost::uuids::uuid HEIFImageUUID;
    pthread_t mUuid_thread;
    psqlDebayer *psqlD;
    ImageBuffer *uuidImageBuffer;
    std::atomic_bool needStop;
    void sendMetaToPostgresThread();
    static void* stopThread(mUUIDv5*);
    boost::uuids::uuid generateRawUUID(std::string, std::string);
    boost::uuids::uuid generateJpegUUID(std::string, std::string);
    boost::uuids::uuid generateHeifiUUID(std::string, std::string);
    boost::uuids::string_generator mGen;
    private:
    void* resultThread;
    mUUIDv5();
    ~mUUIDv5();
};
