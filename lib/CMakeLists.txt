
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

FetchContent_MakeAvailable(amqpcpp)
FetchContent_MakeAvailable(tinygltf)
FetchContent_MakeAvailable(spdlog)

add_subdirectory(SketchUpSDK)
