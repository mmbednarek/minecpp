cmake_minimum_required(VERSION 3.15)
project(minecpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Werror -Wno-unknown-pragmas")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(ENET_PROVIDER "library" CACHE STRING "ENetProvider")

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams system program_options)
find_package(GTest REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(absl REQUIRED)

find_library(FDB_LIBRARY_PATH NAMES fdb_c)
if (FDB_LIBRARY_PATH)
    message(STATUS "Found FDB: ${FDB_LIBRARY_PATH}")
    add_library(fdb::fdb SHARED IMPORTED)
    set_property(TARGET fdb::fdb PROPERTY IMPORTED_LOCATION ${FDB_LIBRARY_PATH})
else()
    message(FATAL_ERROR "Failed to find FDB library")
endif()

if (${ENET_PROVIDER} STREQUAL "library")
    find_library(ENET_LIBRARY_PATH NAMES enet)
    if (ENET_LIBRARY_PATH)
        message(STATUS "Found eNET: ${ENET_LIBRARY_PATH}")
        add_library(enet::enet SHARED IMPORTED)
        set_property(TARGET enet::enet PROPERTY IMPORTED_LOCATION ${ENET_LIBRARY_PATH})
    else()
        message(FATAL_ERROR "Failed to find eNET library")
    endif()
else()
    find_package(ENet REQUIRED)
endif()

include(CTest)
include(FetchContent)

find_package(Protobuf REQUIRED)

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
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(yaml-cpp PUBLIC -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-shadow -Wno-unused-parameter)
    target_compile_options(yaml-cpp-read PRIVATE -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-shadow -Wno-unused-parameter)
    target_compile_options(yaml-cpp-parse PRIVATE -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-shadow -Wno-unused-parameter)
    target_compile_options(yaml-cpp-sandbox PRIVATE -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-shadow -Wno-unused-parameter)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(yaml-cpp PUBLIC -Wno-conversion -Wno-shadow -Wno-unused-parameter -Wno-restrict)
    target_compile_options(yaml-cpp-read PRIVATE -Wno-conversion -Wno-shadow -Wno-unused-parameter -Wno-restrict)
    target_compile_options(yaml-cpp-parse PRIVATE -Wno-conversion -Wno-shadow -Wno-unused-parameter -Wno-restrict)
    target_compile_options(yaml-cpp-sandbox PRIVATE -Wno-conversion -Wno-shadow -Wno-unused-parameter -Wno-restrict)
else ()
    message(FATAL_ERROR "Unsupported compiler")
endif ()

FetchContent_Declare(
        libmb
        GIT_REPOSITORY https://github.com/mmbednarek/mb
        GIT_TAG libmb-0.0.33
)
FetchContent_MakeAvailable(libmb)

FetchContent_Declare(
        libmb_codegen
        GIT_REPOSITORY https://github.com/mmbednarek/codegen
        GIT_TAG codegen-0.0.40
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
