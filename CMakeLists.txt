cmake_minimum_required(VERSION 3.15)
project(minecpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

find_package(Boost REQUIRED COMPONENTS iostreams system program_options)
find_package(Protobuf REQUIRED)

include(FetchContent)

set(gRPC_PROTOBUF_PROVIDER "package")

FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG v1.38.1
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
        GIT_TAG v1.8.2
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
        GIT_TAG 7.1.3
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
        libmb
        GIT_REPOSITORY https://github.com/mmbednarek/mb
        GIT_TAG libmb-0.0.18
)
FetchContent_MakeAvailable(libmb)

FetchContent_Declare(
        libmb_codegen
        GIT_REPOSITORY https://github.com/mmbednarek/codegen
        GIT_TAG codegen-0.0.17
)
FetchContent_MakeAvailable(libmb_codegen)

include_directories(./include)
include_directories(./service/protos/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")

# Libraries

add_subdirectory(lib/api/minecpp/proto)
add_subdirectory(lib/api/minecpp/nbt)
add_subdirectory(lib/chat)
add_subdirectory(lib/error)
add_subdirectory(lib/format)
add_subdirectory(lib/squeezed)
add_subdirectory(lib/random)
add_subdirectory(lib/util)
add_subdirectory(lib/player)
add_subdirectory(lib/nbt)
add_subdirectory(lib/region)
add_subdirectory(lib/game)
add_subdirectory(lib/network)
add_subdirectory(lib/event)
add_subdirectory(lib/service/discovery)
add_subdirectory(lib/service/engine)

# Tests

add_subdirectory(test)

# Tools

add_subdirectory(tool/nbt_viewer)
add_subdirectory(tool/chunk_extractor)
add_subdirectory(tool/chunk_viewer)
add_subdirectory(tool/recipes)
add_subdirectory(tool/statelist)
add_subdirectory(tool/nbtprotogen)
add_subdirectory(tool/nbtscheme)
add_subdirectory(tool/discocli)

# Services

add_subdirectory(service/protos/include/minepb)
add_subdirectory(service/chunk_storage)
add_subdirectory(service/engine)
add_subdirectory(service/front)
add_subdirectory(service/discovery)
