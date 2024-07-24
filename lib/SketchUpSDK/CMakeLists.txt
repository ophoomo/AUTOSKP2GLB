

set(SKETCHUP_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_path(SKETCHUP_INCLUDE_DIR
        NAMES SketchUpAPI/sketchup.h
        PATHS ${SKETCHUP_SDK_PATH}/headers
)

if(NOT SKETCHUP_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find the SketchUp SDK headers")
endif()

find_library(SKETCHUP_LIBRARY
        NAMES SketchUpAPI
        PATHS ${SKETCHUP_SDK_PATH}/binaries/sketchup/x64
)

if(NOT SKETCHUP_LIBRARY)
    message(FATAL_ERROR "Could not find the SketchUp SDK library")
endif()