set(MINECPP_ENGINE_API_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_engine_api STATIC)

# Public include headers
target_include_directories(minecpp_engine_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_engine_api
        LINK_PRIVATE
        minecpp_api_proto
        minecpp_event
        minecpp_game
        minecpp_grpc
        grpc++
        libmb
        fmt
        spdlog
)
