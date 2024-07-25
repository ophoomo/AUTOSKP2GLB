#include "header/storage.h"

#include "miniocpp/client.h"
#include "miniocpp/request.h"
#include "spdlog/spdlog.h"

minio::s3::Client setup(const StorageConfig& storage_config) {
    minio::s3::BaseUrl base_url(storage_config.host);

    minio::creds::StaticProvider provider(
      storage_config.access_key, storage_config.secret_key);
    minio::s3::Client client(base_url, &provider);

    std::string bucket_name = storage_config.bucket_name;

    bool exist;
    {
        minio::s3::BucketExistsArgs args;
        args.bucket = bucket_name;

        minio::s3::BucketExistsResponse resp = client.BucketExists(args);
        if (!resp) {
            spdlog::error("unable to do bucket existence check {}", resp.Error());
        }

        exist = resp.exist;
    }

    if (!exist) {
        minio::s3::MakeBucketArgs args;
        args.bucket = bucket_name;

        minio::s3::MakeBucketResponse resp = client.MakeBucket(args);
        if (!resp) {
            spdlog::error("unable to create bucket {}", resp.Error());
        }
    }

    return client;
}

std::string download_file(minio::s3::Client client) {
    std::string path_file;
    minio::s3::DownloadObjectArgs args = {};
    // args.bucket = bucket_name;
    // args.object = name_file;
    // args.filename = path_file;

    minio::s3::DownloadObjectResponse resp = client.DownloadObject(args);
    if (!resp) {
        spdlog::error("unable to download object {}", resp.Error());
    }

    // spdlog::info("{} is successfully downloaded as object {} to bucket {}", path_file, name_file, bucket_name);
    return path_file;
}

void upload_file(minio::s3::Client client) {

    minio::s3::UploadObjectArgs args = {};
    // args.bucket = bucket_name;
    // args.object = name_file;
    // args.filename = path_file;

    minio::s3::UploadObjectResponse resp = client.UploadObject(args);
    if (!resp) {
        spdlog::error("unable to upload object {}", resp.Error());
    }

    // spdlog::info("{} is successfully uploaded as object {} to bucket {}", path_file, name_file, bucket_name);
}
