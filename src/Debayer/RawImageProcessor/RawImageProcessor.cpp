// RawImageProcessor.cpp : Defines the entry point for the application.
//
#include "RawImageProcessor.h"
#include "../UUID/UUID.h"
/*using namespace std;

int main()
{
    RawImageProcessor mRIP;

    //CuviPipeline CuPi;
    if(!mRIP.start())
        cout << "process isnt started correctly" << endl;
    int i=0;
   // const string filepath = "somefilejpg";
    while(i)
    {
       // CuPi.runPipeline(1,filepath,(void*)NULL);
        i++;
    };
    mRIP.stop();

    return 0;
}
*/

bool RawImageProcessor::start(ImageBuffer* bufferFromMain)
{
    image_buffer=bufferFromMain;
    if(pthread_create(&mThreadStruct.mProcessingThread,NULL,rawThread,(void*)this))
    {
        mThreadStruct.isStarted=false;
        return false;
    }

//    if(!(blob=AzureBlob::startThread("/tmp/shit"))) // if thread is not started, return false.
//        return false;
    mThreadStruct.isStarted = true;
    return true;
}

bool RawImageProcessor::stop()
{
    mThreadStruct.needStop.store(true,std::memory_order_relaxed);
    //some broadcast maybe
    if(!pthread_join(mThreadStruct.mProcessingThread,NULL))
        return true;
}

RawImageProcessor::RawImageProcessor()
{
    pthread_mutex_init (&deque_mtx,NULL);
    pthread_mutex_init (&buffer_mtx,NULL);
    pthread_mutex_init (&data_mtx,NULL);
    pthread_mutex_init (&meta_mtx,NULL);
}

RawImageProcessor::~RawImageProcessor()
{
     pthread_mutex_destroy (&deque_mtx);
     pthread_mutex_destroy (&buffer_mtx);
     pthread_mutex_destroy (&data_mtx);
     pthread_mutex_destroy (&meta_mtx);
}

void* rawThread(void * args)
{
    pthread_setname_np(pthread_self(),"rawThread");
    RawImageProcessor* RIP = (RawImageProcessor*) args;
//    CuviPipeline CuPi;
    mUUIDv5* uuuid = mUUIDv5::createThread(RIP->image_buffer);
    // Define the connection-string with your values.
//    const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=your_storage_account;AccountKey=your_storage_account_key"));

    try {
        // Retrieve storage account from connection string.
//        azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(utility::conversions::to_utf8string(storage_connection_string));

//        // Create the blob client.
//        azure::storage::cloud_blob_client blob_client = storage_account.create_cloud_blob_client();

//        // Retrieve a reference to a container.
//        azure::storage::cloud_blob_container container = blob_client.get_container_reference(U("my-sample-container"));

//        // Create the container if it doesn't already exist.
//        container.create_if_not_exists();
//        // Make the blob container publicly accessible.
//        azure::storage::blob_container_permissions permissions;
//        permissions.set_public_access(azure::storage::blob_container_public_access_type::blob);
//        container.upload_permissions(permissions);


//        // Create or overwrite the "my-blob-1" blob with contents from a local file.
//        concurrency::streams::istream input_stream = concurrency::streams::file_stream<uint8_t>::open_istream(U("DataFile.txt")).get();

//        input_stream.close().wait();
        while(!RIP->mThreadStruct.needStop.load(std::memory_order_relaxed))
        {
            while(!RIP->image_buffer->ImagesWithMeta->empty())
               {
//                   CuPi.runPipeline(RIP->image_buffer->ImagesWithFrameIds->front().frameId,std:: string filepath,RIP->image_buffer->ImagesWithFrameIds->front().void_frame);
//                  uuuid->RawImageUUID = uuuid->generateRawUUID("timestamp","md5");
//                    pthread_mutex_lock(&uuuid->uuidImageBuffer->image_processing_mutex);
//                    azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(U("my-blob-"+std::to_string(RIP->image_buffer->ImagesWithMeta->front().mMeta.raw_frame_id)));
//                    blockBlob.upload_from_stream(input_stream);
//                    input_stream.close().wait();
                    sleep(1);
                };
        sleep(1);
        }
    }  catch (const std::exception& e)
    {
        std::wcout<<e.what()<<endl;
        mUUIDv5::stopThread(uuuid);
    }
    mUUIDv5::stopThread(uuuid);
    pthread_exit(NULL);
}


