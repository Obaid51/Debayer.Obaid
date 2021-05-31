#include "azureblob.h"

AzureBlob *AzureBlob::startThread(std::string path_to_dir)
{
    AzureBlob *blob = new AzureBlob;
    blob->mPath = path_to_dir;
    if(!pthread_create(&blob->mThread,NULL,AzureBlobThread,blob))
        return blob;
}

void *AzureBlobThread(void* args)
{
    pthread_setname_np(pthread_self(),"AzureBlob");
    AzureBlob* blob = (AzureBlob*) args;
    const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=your_storage_account;AccountKey=your_storage_account_key"));
    azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(utility::conversions::to_utf8string(storage_connection_string));
    azure::storage::cloud_blob_client blob_client = storage_account.create_cloud_blob_client();
    azure::storage::cloud_blob_container container = blob_client.get_container_reference(U("my-sample-container"));
    container.create_if_not_exists();
    azure::storage::blob_container_permissions permissions;
    permissions.set_public_access(azure::storage::blob_container_public_access_type::blob);
    container.upload_permissions(permissions);

    while(!blob->needStop.load())
    {
        for (auto & p : fs::directory_iterator(blob->mPath))
        {
            concurrency::streams::istream input_stream = concurrency::streams::file_stream<uint8_t>::open_istream(U(p.path().generic_string())).get();
            azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(U("my-blob-"));
            blockBlob.upload_from_stream(input_stream);
            input_stream.close().wait();
            fs::remove(p);
        }
    }
    pthread_exit(NULL);
}
