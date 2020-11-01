cmake_minimum_required(VERSION 3.15)
project(minecpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(boost-cmake)
include_directories(${Boost_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG v1.25.0
)
FetchContent_MakeAvailable(gRPC)

FetchContent_Declare(
        yaml
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
        GIT_TAG yaml-cpp-0.6.3
)
FetchContent_MakeAvailable(yaml)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG v1.6.1
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(gtest)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 7.0.3
)
FetchContent_MakeAvailable(fmt)

include_directories(./lib)
include_directories(./services/protos/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter -fconcepts")

add_subdirectory(lib/chat)
add_subdirectory(lib/error)
add_subdirectory(lib/format)
add_subdirectory(lib/squeeze)
add_subdirectory(lib/minerandom)
add_subdirectory(lib/mineutils)
add_subdirectory(lib/nbt)
add_subdirectory(lib/region)
add_subdirectory(lib/game)
add_subdirectory(lib/minenet)
add_subdirectory(tests)

add_subdirectory(tools/nbt_viewer)
add_subdirectory(tools/chunk_extractor)
add_subdirectory(tools/chunk_viewer)
add_subdirectory(tools/recipes)
add_subdirectory(tools/statelist)
add_subdirectory(tools/nbtprotogen)
add_subdirectory(tools/nbtscheme)
add_subdirectory(services/protos/include/minepb)
add_subdirectory(services/chunk_storage)
add_subdirectory(services/engine)
add_subdirectory(services/front)
