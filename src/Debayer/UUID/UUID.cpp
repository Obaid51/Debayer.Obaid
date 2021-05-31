#include "UUID.h"


boost::uuids::uuid mUUIDv5::generateRawUUID(std::string timestamp,std::string md5 )
{
    boost::uuids::name_generator RawUUIDgen(RAW_namespace);
    return RawUUIDgen(timestamp+md5);
}

boost::uuids::uuid mUUIDv5::generateJpegUUID(std::string timestamp,std::string md5 )
{
    boost::uuids::name_generator JPEGUUIDgen(JPEG_namespace);
    return JPEGUUIDgen(timestamp+md5);
}

boost::uuids::uuid mUUIDv5::generateHeifiUUID(std::string timestamp,std::string md5 )
{
    boost::uuids::name_generator HEIFUUIDgen(HEIF_namespace);
    return HEIFUUIDgen(timestamp+md5);
}

void* mUUIDv5::stopThread(mUUIDv5* uuid)
{
    uuid->needStop.store(true,std::memory_order_relaxed);
    pthread_join(uuid->mUuid_thread,&uuid->resultThread);
    void* resultThread = uuid->resultThread;
    uuid->psqlD->stopThread(uuid->psqlD);
    delete uuid;
    return resultThread;
}



void* uuid_thread(void* args)
{
    pthread_setname_np(pthread_self(),"uuid_thread");
    mUUIDv5* uuid_obj = (mUUIDv5*) args;
    try
    {
        while(!uuid_obj->needStop.load(std::memory_order_relaxed))
        {
            pthread_mutex_lock(&uuid_obj->sended_uuid_mtx);
            if(!uuid_obj->queImages.empty())
                pthread_cond_wait(&uuid_obj->sended_uuid_cond,&uuid_obj->sended_uuid_mtx);
            while(!uuid_obj->queImages.empty())
            {
                pthread_mutex_lock(&uuid_obj->uuidImageBuffer->meta_processing_mutex);
                imageMetaInfo meta = uuid_obj->uuidImageBuffer->ImagesWithMeta->front().mMeta;
                pthread_mutex_unlock(&uuid_obj->uuidImageBuffer->meta_processing_mutex);
                switch (meta.mImageFormat)
                {
                    case raw: meta.imageId   =     uuid_obj->generateRawUUID("meta.mCaptureTimeStamp","meta.mRawHash");      break;
                    case jpg: meta.imageId   =     uuid_obj->generateJpegUUID("meta.mCuViTimeStamp","meta.mJpegHash");       break;
                    case heifi: meta.imageId =     uuid_obj->generateHeifiUUID("meta.mCuViTimeStamp","meta.mJpegHash");      break;
                default: printf("bad type %i ",meta.mImageFormat);
                };
                pthread_mutex_lock(&uuid_obj->psqlD->meta_mtx);
                uuid_obj->psqlD->mMeta.push(meta);
                pthread_mutex_lock(&uuid_obj->psqlD->meta_mtx);
                pthread_cond_signal(&uuid_obj->psqlD->meta_sended);
            }
            pthread_mutex_unlock(&uuid_obj->sended_uuid_mtx);
        }
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << '\n';
        return (void*)1;
    }



    pthread_exit(0);
}

mUUIDv5* mUUIDv5::createThread(ImageBuffer* mainbuffer)
{
    mUUIDv5* some_uuid_obj = new mUUIDv5();
    some_uuid_obj->psqlD = psqlDebayer::startThread();
    some_uuid_obj->uuidImageBuffer = mainbuffer;
    if(!pthread_create(&some_uuid_obj->mUuid_thread,NULL,uuid_thread,some_uuid_obj))
        return some_uuid_obj;
    else return 0;
}

void mUUIDv5::sendMetaToPostgresThread()
{
//    pthread_cond_signal(postgres_condition);
}
mUUIDv5::mUUIDv5()
{
    needStop.store(false,std::memory_order_relaxed);
    pthread_mutex_init(&sended_uuid_mtx, NULL);
    pthread_mutex_init(&que_mtx,NULL);
    pthread_mutex_init(&started_mutex,NULL);
    pthread_cond_init(&sended_uuid_cond, NULL);
//    pthread_cond_init(&thread_started_cond,NULL);
    RAW_namespace = mGen("{67fb4f81-d9f7-46db-b35f-64b3ec9d7492}");
    JPEG_namespace= mGen("{3235cd98-cdb1-416c-8609-a48c90aa2c34}");
    HEIF_namespace= mGen("{6500431b-9f4e-4c93-ae3e-1fe818845a53}");
}

mUUIDv5::~mUUIDv5()
{
    pthread_mutex_destroy(&que_mtx);
//    pthread_cond_destroy(&thread_started_cond);
    pthread_cond_destroy(&sended_uuid_cond);
    pthread_mutex_destroy(&sended_uuid_mtx);
    pthread_mutex_destroy(&started_mutex);
}

/*
int main()
{
    mUUIDv5* mUUD = mUUIDv5::createThread();

//    pthread_cond_wait(&mUUD->thread_started_cond,&mUUD->started_mutex);
    for (int i = 0;i<50;i++)
    {

        imageMetaInfo meta;
        meta.mCaptureTimeStamp = std::time(NULL);
        std::string ti_me = boost::lexical_cast<std::string>(meta.mCaptureTimeStamp);
        std::string md_5 = md5(ti_me);
        switch(i%2){
        case 0 :
            meta.mRawHash = md_5;
            meta.id = mUUD->generateRawUUID(ti_me,md_5);
            break;
        case 1 :
            meta.mJpegHash = md_5;
            meta.id = mUUD->generateJpegUUID(ti_me,md_5);
            break;
        }
        pthread_mutex_lock(&mUUD->que_mtx);
        mUUD->queImages.push(meta);
        pthread_mutex_unlock(&mUUD->que_mtx);
        pthread_cond_signal(&mUUD->sended_uuid_cond);
        sleep(1);
    }
    while(!mUUD->queImages.empty())
    {
        usleep(1);
    }
    mUUIDv5::stopThread(mUUD);
}
*/
