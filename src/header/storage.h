#ifndef STORAGE_H
#define STORAGE_H

#include "miniocpp/client.h"

struct StorageConfig {
    std::string host;
    std::string access_key;
    std::string secret_key;
    std::string bucket_name;
};

minio::s3::Client setup(const StorageConfig& storage_config);
std::string download_file(minio::s3::Client client);
void upload_file(minio::s3::Client client);

#endif //STORAGE_H
