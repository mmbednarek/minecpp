cmake_minimum_required(VERSION 3.15)
project(minecpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include(FetchContent)
FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG        v1.25.0
)
FetchContent_MakeAvailable(gRPC)

FetchContent_Declare(
        yaml
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
        GIT_TAG        yaml-cpp-0.6.3
)
FetchContent_MakeAvailable(yaml)

add_subdirectory(boost-cmake)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src/api/pbcpp)
add_subdirectory(src/common/utils)
add_subdirectory(src/common/log)
add_subdirectory(src/common/nbt)
add_subdirectory(src/common/region)
add_subdirectory(src/common/game)
add_subdirectory(src/tests)

add_subdirectory(src/tools/nbt_viewer)
add_subdirectory(src/tools/chunk_extractor)
add_subdirectory(src/chunk_storage)
add_subdirectory(src/front)
