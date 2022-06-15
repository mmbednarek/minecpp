SET(MINECPP_GAME_CONTROLLER_BLOCK_INCLUDE_DIR ${MINECPP_GAME_CONTROLLER_INCLUDE_DIR}/block)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_CONTROLLER_BLOCK_INCLUDE_DIR}/Default.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Default.cpp
)
