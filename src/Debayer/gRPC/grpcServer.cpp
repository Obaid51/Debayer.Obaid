
#include <gRPC/grpcServer.h>

class TransferServiceImpl final : public Transfer::Service
{
	Status FileStream(::grpc::ServerContext *context, ::grpc::ServerReader<::filestream::Image> *reader, ::filestream::TransferResponse *response) override
	{

        filestream::Image* message = nullptr;
        reader->Read(message);
        std::string md5_hash = "";
        if(message->has_imagechunk())
            md5_hash = md5(message->imagechunk().framechunk());
        else
            return Status::CANCELLED;
        // std::string image_hash_computed("This is a fake has for the moment");
		// auto image_hashed_with = filestream::HashAlgorithm::SHA1;
		// auto image_hash = filestream::ImageHash();

//		 image_hash.set_filehash(image_hash_computed);
		// image_hash.set_hashalgorithm(image_hashed_with);

//		 response->set_allocated_imagehash(&image_hash);
//        mThreadData.void_frame_deque.push((void*)&message->imagechunk().framechunk());
        mThreadData.reiceved_images_deque.push_front(*message);
        pthread_cond_signal(&mThreadData.sended_image_cond);
        response->set_allocated_imagehash((filestream::ImageHash*)&md5_hash);
        response->set_size(700);
		return Status::OK;
	};

public:
    struct threadData{
        threadData()
        {
            pthread_mutex_init(&recieved_image_mtx,NULL);
            pthread_mutex_init(&recieve_que_mtx,NULL);
            pthread_mutex_init(&processing_que_mtx,NULL);
            pthread_cond_init(&sended_image_cond,NULL);
        };
        ~threadData()
        {
            pthread_mutex_destroy(&recieved_image_mtx);
            pthread_mutex_destroy(&recieve_que_mtx);
            pthread_mutex_destroy(&processing_que_mtx);
            pthread_cond_destroy(&sended_image_cond);
        };

        // deque of images, needs to be stored and processed
        std::deque<filestream::Image> reiceved_images_deque;

        // deque of images, there are stored and processing now
        std::deque<std::string> deque_of_images_processing;

        mBuffer *imageBuffer;

        pthread_t grpc_server_thread;
        pthread_mutex_t recieved_image_mtx;
        pthread_mutex_t recieve_que_mtx;
        pthread_mutex_t processing_que_mtx;
        pthread_cond_t sended_image_cond;
        std::atomic_bool needStop;
    } mThreadData;


};

void* send_image_thread(void* args)
{
   TransferServiceImpl::threadData *threadData = (TransferServiceImpl::threadData*) args;
    pthread_setname_np(pthread_self(),"send_image_thread");
    while(!threadData->needStop)
    {
        pthread_mutex_lock(&threadData->recieved_image_mtx);
        if(!threadData->reiceved_images_deque.empty())
            pthread_cond_wait(&threadData->sended_image_cond,&threadData->recieved_image_mtx);
        while(!threadData->reiceved_images_deque.empty())
        {
            pthread_mutex_lock(&threadData->recieve_que_mtx);
            // Recieve images and store them for process later
                threadData->deque_of_images_processing.push_front(threadData->reiceved_images_deque.front().imagechunk().framechunk());
                threadData->reiceved_images_deque.pop_front();
            pthread_mutex_unlock(&threadData->recieve_que_mtx);
            // Send void* image to buffer
            threadData->imageBuffer->void_frame_queue->push((void*)&threadData->deque_of_images_processing.front());
         }

        pthread_mutex_unlock(&threadData->recieved_image_mtx);
    }
    pthread_exit(0);
};

void* clear_deque_thread(void* args)
{
    TransferServiceImpl::threadData *threadData = (TransferServiceImpl::threadData*)args;
    pthread_setname_np(pthread_self(),"clear_deque_thread");
//    pthread_cond_wait();
    while(threadData->imageBuffer->frames_processed>0)
    {
        threadData->deque_of_images_processing.pop_back();
    }
}

void RunGrpcServer(mBuffer *m_buffer)
{
	// TODO: Set the port number based on env vars
	BOOST_LOG_TRIVIAL(info) << "Port: 50051" << endl;
	std::string server_address("0.0.0.0:50051");
	TransferServiceImpl service = TransferServiceImpl();

	grpc::EnableDefaultHealthCheckService(true); // TODO: If dev environment or debug. set to true, else false.
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	ServerBuilder builder;
	// Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&service);
	// Finally assemble the server.
	std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    service.mThreadData.imageBuffer = m_buffer;
    pthread_create(&service.mThreadData.grpc_server_thread,NULL,send_image_thread,&service.mThreadData);

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.

	server->Wait();
}
