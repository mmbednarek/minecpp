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

include_directories(./lib)
include_directories(./services/protos/include)

add_subdirectory(lib/mineutils)
add_subdirectory(lib/nbt)
add_subdirectory(lib/region)
add_subdirectory(lib/game)
add_subdirectory(lib/minenet)
add_subdirectory(./tests)

add_subdirectory(tools/nbt_viewer)
add_subdirectory(tools/chunk_extractor)
add_subdirectory(tools/recipes)
add_subdirectory(services/protos/include/minepb)
add_subdirectory(services/chunk_storage)
add_subdirectory(services/front)
