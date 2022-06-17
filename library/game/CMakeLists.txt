set(MINECPP_GAME_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_game)

# Public include headers
target_include_directories(minecpp_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_game
        LINK_PUBLIC
        minecpp_api_nbt
        minecpp_chat
        minecpp_error
        minecpp_utils
        minecpp_nbt
        minecpp_squeeze
        minecpp_random
        spdlog
        ${Protobuf_LIBRARIES}
        grpc++
)
