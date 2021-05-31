 #include "psqlDebayer.h"

psqlDebayer::psqlDebayer()
{
    pthread_cond_init(&meta_sended,NULL);
    pthread_mutex_init(&meta_mtx,NULL);
    needStop = false;
};
psqlDebayer::~psqlDebayer()
{
    pthread_cond_destroy(&meta_sended);
    pthread_mutex_destroy(&meta_mtx);
};

psqlDebayer* psqlDebayer::startThread()
{
    psqlDebayer* psqlD = new psqlDebayer;
    if(!pthread_create(&psqlD->mThread,NULL,send_to_db,psqlD))
        return psqlD;
    else throw;
};

void psqlDebayer::stopThread(psqlDebayer* psqlD)
{
    psqlD->needStop = true;
    pthread_mutex_lock(&psqlD->meta_mtx);
    pthread_cond_signal(&psqlD->meta_sended);
    pthread_mutex_unlock(&psqlD->meta_mtx);
    pthread_join(psqlD->mThread,NULL);
    delete psqlD;
}

void *send_to_db(void* args)
{
    psqlDebayer* psqlD = (psqlDebayer*) args;
 //   pqxx::connection c;
       std::ostringstream conn_string("");
    conn_string << "host=" << getenv("POSTGRES_SERVER")
                << " user=" << getenv("POSTGRES_USER")
                << " password=" << getenv("POSTGRES_PASSWORD")
                << " dbname=" << getenv("POSTGRES_DATABASE");
    pqxx::connection c ( conn_string.str() ) ;
    while(!psqlD->needStop)
    {
        pthread_mutex_lock(&psqlD->meta_mtx);
        pthread_cond_wait(&psqlD->meta_sended,&psqlD->meta_mtx);
        imageMetaInfo meta;
        if(!psqlD->mMeta.empty())
            imageMetaInfo meta = psqlD->mMeta.top();
        pthread_mutex_unlock(&psqlD->meta_mtx);
        pqxx::work W{c};
        while(!psqlD->mMeta.empty())
        {
            std::string insert_row="INSERT INTO debayer (image_id,image_capture_timestamp_raw) VALUES ('"+boost::uuids::to_string(meta.imageId)+"','"+boost::lexical_cast<std::string>(meta.mCaptureTimeStamp)+"');";
            W.exec0(insert_row);
            psqlD->mMeta.pop();
        }
        W.commit();
    }
    return 0;
};
