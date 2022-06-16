add_library(minecpp_game)
add_subdirectory("src")

target_link_libraries(minecpp_game
        LINK_PUBLIC
        minecpp_utils
        minecpp_nbt
        minecpp_api_nbt
        minecpp_error
        minecpp_squeeze
        minecpp_random
        spdlog
        ${Protobuf_LIBRARIES}
        grpc++
)
