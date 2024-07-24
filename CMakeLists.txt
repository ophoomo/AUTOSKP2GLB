cmake_minimum_required(VERSION 3.28)
project(auto-skp2glb)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${SKETCHUP_INCLUDE_DIR})

add_subdirectory(lib)
add_subdirectory(src)


