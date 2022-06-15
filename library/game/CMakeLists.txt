set(MINECPP_GAME_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/game)

add_library(minecpp_game
        # Source files
        Rules.cpp
        World.cpp

        # Header files
        ${MINECPP_GAME_INCLUDE_DIR}/Chunks.h
        ${MINECPP_GAME_INCLUDE_DIR}/Game.h
        ${MINECPP_GAME_INCLUDE_DIR}/Hand.h
        ${MINECPP_GAME_INCLUDE_DIR}/Mode.h
        ${MINECPP_GAME_INCLUDE_DIR}/Notifier.h
        ${MINECPP_GAME_INCLUDE_DIR}/Rules.h
        ${MINECPP_GAME_INCLUDE_DIR}/State.h
        ${MINECPP_GAME_INCLUDE_DIR}/World.h
)

add_subdirectory("block")
add_subdirectory("chunk")
add_subdirectory("entity")
add_subdirectory("item")
add_subdirectory("worldgen")

target_link_libraries(minecpp_game LINK_PUBLIC minecpp_utils minecpp_nbt minecpp_api_nbt minecpp_error minecpp_squeeze spdlog ${Protobuf_LIBRARIES} grpc++)