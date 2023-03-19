cmake_minimum_required(VERSION 3.15)
project(minecpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Werror -Wno-unknown-pragmas")

option(USE_LOCAL_GPRC "Compile using local gRPC and Protobuf libraries" ON)

set(gRPC_PROTOBUF_PROVIDER "package")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

option(BUILD_FMT_SOURCE "The build source of fmt library" "conan")

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams system program_options)
find_package(GTest REQUIRED)
find_package(OpenSSL REQUIRED)

find_library(FDB_LIBRARY NAMES fdb_c)

include(CTest)
include(FetchContent)

if (${USE_LOCAL_GPRC})
    find_package(absl REQUIRED)
    find_package(Protobuf REQUIRED)
    find_package(gRPC CONFIG REQUIRED)
else ()
    FetchContent_Declare(
            gRPC
            GIT_REPOSITORY https://github.com/grpc/grpc
            GIT_TAG v1.46.0
    )
    FetchContent_MakeAvailable(gRPC)
endif ()

if (${SPDLOG_FMT_EXTERNAL})
    add_definitions(-DSPDLOG_FMT_EXTERNAL=1)
endif ()

if (${FDB_API_VERSION})
    add_definitions(-DFDB_API_VERSION=${FDB_API_VERSION})
endif ()

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
        GIT_TAG yaml-cpp-0.7.0
)
FetchContent_MakeAvailable(yaml-cpp)

# Disable warnings for yaml-cpp
target_compile_options(yaml-cpp PUBLIC -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-shadow -Wno-unused-parameter)
target_compile_options(yaml-cpp-read PRIVATE -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-shadow -Wno-unused-parameter)
target_compile_options(yaml-cpp-parse PRIVATE -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-shadow -Wno-unused-parameter)
target_compile_options(yaml-cpp-sandbox PRIVATE -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-shadow -Wno-unused-parameter)

FetchContent_Declare(
        libmb
        GIT_REPOSITORY https://github.com/mmbednarek/mb
        GIT_TAG libmb-0.0.33
)
FetchContent_MakeAvailable(libmb)

FetchContent_Declare(
        libmb_codegen
        GIT_REPOSITORY https://github.com/mmbednarek/codegen
        GIT_TAG codegen-0.0.32
)
FetchContent_MakeAvailable(libmb_codegen)

FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt
        GIT_TAG v3.11.1
)
FetchContent_MakeAvailable(entt)

# Libraries
add_subdirectory(library)

# Tools
add_subdirectory(tool)

# Services
add_subdirectory(service)