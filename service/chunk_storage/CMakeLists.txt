set(MINECPP_CHUNK_STORAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(minecpp_chunk_storage)

# Public include headers
target_include_directories(minecpp_chunk_storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_chunk_storage
        LINK_PUBLIC
        minecpp_utils
        minecpp_game
        minecpp_network
        minecpp_region
        minecpp_api_proto
        minecpp_random
        minecpp_repository
        minecpp_world
        grpc++
        Boost::system
        spdlog
        libmb
)
