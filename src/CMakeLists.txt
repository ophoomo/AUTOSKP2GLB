

add_executable(${PROJECT_NAME}
        main.cpp
        header/convert.h
        convert.cpp
        header/mqtt.h
        storage.cpp
        header/storage.h
        mqtt.cpp
        header/extract.h
        extract.cpp
        header/gltf.h
        gltf.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE miniocpp::miniocpp)
target_link_libraries(${PROJECT_NAME} PRIVATE amqpcpp)
target_link_libraries(${PROJECT_NAME} PRIVATE tinygltf)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SKETCHUP_LIBRARY})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/SketchUpSDK/binaries/sketchup/x64/SketchUpAPI.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/SketchUpSDK/binaries/sketchup/x64/SketchUpCommonPreferences.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

