

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE amqpcpp)
target_link_libraries(${PROJECT_NAME} PRIVATE tinygltf)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SKETCHUP_LIBRARY})
