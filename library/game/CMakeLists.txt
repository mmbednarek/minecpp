set(MINECPP_GAME_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/game)

add_library(minecpp_game
        # Source files
        rules.cpp
        world.cpp

        # Header files
        ${MINECPP_GAME_INCLUDE_DIR}/block_controller.h
        ${MINECPP_GAME_INCLUDE_DIR}/chunks.h
        ${MINECPP_GAME_INCLUDE_DIR}/game.h
        ${MINECPP_GAME_INCLUDE_DIR}/hand.h
        ${MINECPP_GAME_INCLUDE_DIR}/mode.h
        ${MINECPP_GAME_INCLUDE_DIR}/notifier.h
        ${MINECPP_GAME_INCLUDE_DIR}/rules.h
        ${MINECPP_GAME_INCLUDE_DIR}/state.h
        ${MINECPP_GAME_INCLUDE_DIR}/world.h
)

add_subdirectory("block")
add_subdirectory("chunk")
add_subdirectory("entity")
add_subdirectory("item")
add_subdirectory("worldgen")

target_link_libraries(minecpp_game LINK_PUBLIC minecpp_utils minecpp_nbt minecpp_api_nbt minecpp_error minecpp_squeeze spdlog ${Protobuf_LIBRARIES} grpc++)