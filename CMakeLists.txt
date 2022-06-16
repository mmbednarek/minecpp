cmake_minimum_required(VERSION 3.15)
project(minecpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Wno-unknown-pragmas")

option(USE_LOCAL_GPRC "Compile using local gRPC and Protobuf libraries" ON)

set(gRPC_PROTOBUF_PROVIDER "package")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

SET(MINECPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/minecpp)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams system program_options)
find_package(GTest REQUIRED)

include(FetchContent)

if(${USE_LOCAL_GPRC})
  find_package(absl REQUIRED)
  find_package(Protobuf REQUIRED)
  find_package(gRPC CONFIG REQUIRED)
else()
  FetchContent_Declare(
    gRPC
    GIT_REPOSITORY https://github.com/grpc/grpc
    GIT_TAG v1.46.0
  )
  FetchContent_MakeAvailable(gRPC)
endif()

if(${SPDLOG_FMT_EXTERNAL})
  add_definitions(-DSPDLOG_FMT_EXTERNAL=1)
endif()

FetchContent_Declare(
  yaml
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
  GIT_TAG yaml-cpp-0.7.0
)
FetchContent_MakeAvailable(yaml)

FetchContent_Declare(
  libmb
  GIT_REPOSITORY https://github.com/mmbednarek/mb
  GIT_TAG libmb-0.0.25
)
FetchContent_MakeAvailable(libmb)

FetchContent_Declare(
  libmb_codegen
  GIT_REPOSITORY https://github.com/mmbednarek/codegen
  GIT_TAG codegen-0.0.30
)
FetchContent_MakeAvailable(libmb_codegen)

include_directories(./include)
include_directories(./service/protos/include)

# Libraries
add_subdirectory(library)

# Tests
add_subdirectory(test)

# Tools
add_subdirectory(tool)

# Services
add_subdirectory(service)