
FetchContent_Declare(
        curlpp
        GIT_REPOSITORY https://github.com/jpbarrette/curlpp
        GIT_TAG 592552a165cc569dac7674cb7fc9de3dc829906f
)

FetchContent_Declare(
        minio-cpp
        GIT_REPOSITORY https://github.com/minio/minio-cpp
        GIT_TAG cd4ef14955201d5ce81e54155ef0980f7c644864
)

FetchContent_Declare(
        amqpcpp
        GIT_REPOSITORY https://github.com/CopernicaMarketingSoftware/AMQP-CPP
        GIT_TAG 19b7136a648dfd60dd7a72a5e145e9b1654305a7
)

FetchContent_Declare(
        tinygltf
        GIT_REPOSITORY https://github.com/syoyo/tinygltf
        GIT_TAG fea67861296293e33e6caee81682261a2700136a
)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG 27cb4c76708608465c413f6d0e6b8d99a4d84302
)

FetchContent_MakeAvailable(curlpp)
FetchContent_MakeAvailable(minio-cpp)
FetchContent_MakeAvailable(amqpcpp)
FetchContent_MakeAvailable(tinygltf)
FetchContent_MakeAvailable(spdlog)

add_subdirectory(SketchUpSDK)

