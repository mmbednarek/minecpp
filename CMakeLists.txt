cmake_minimum_required(VERSION 3.15)
project(minecpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

option(USE_LOCAL_GPRC "Compile using local gRPC and Protobuf libraries" ON)

set(gRPC_PROTOBUF_PROVIDER "package")

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams system program_options)
find_package(GTest REQUIRED)

include(FetchContent)

if (${USE_LOCAL_GPRC})
    find_package(absl REQUIRED)
    find_package(Protobuf REQUIRED)
    find_package(gRPC CONFIG REQUIRED)
else()
    fetchcontent_declare(
            gRPC
            GIT_REPOSITORY https://github.com/grpc/grpc
            GIT_TAG v1.46.0
    )
    fetchcontent_makeavailable(gRPC)
endif()

if (${SPDLOG_FMT_EXTERNAL})
    add_definitions(-DSPDLOG_FMT_EXTERNAL=1)
endif()

fetchcontent_declare(
  yaml
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
  GIT_TAG yaml-cpp-0.7.0
)
fetchcontent_makeavailable(yaml)

fetchcontent_declare(
  libmb
  GIT_REPOSITORY https://github.com/mmbednarek/mb
  GIT_TAG libmb-0.0.21
)
fetchcontent_makeavailable(libmb)

fetchcontent_declare(
  libmb_codegen
  GIT_REPOSITORY https://github.com/mmbednarek/codegen
  GIT_TAG codegen-0.0.27
)
fetchcontent_makeavailable(libmb_codegen)

include_directories(./include)
include_directories(./service/protos/include)

# Libraries

add_subdirectory(lib/api/minecpp/proto)
add_subdirectory(lib/api/minecpp/nbt)
add_subdirectory(lib/repository)
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
add_subdirectory(tool/nbtprotogen)
add_subdirectory(tool/nbtscheme)
add_subdirectory(tool/discocli)
add_subdirectory(tool/dimension)
add_subdirectory(tool/snbt_parser)

# Services

add_subdirectory(service/chunk_storage)
add_subdirectory(service/engine)
add_subdirectory(service/front)
add_subdirectory(service/discovery)
