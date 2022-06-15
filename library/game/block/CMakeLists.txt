SET(MINECPP_GAME_BLOCK_INCLUDE_DIR ${MINECPP_GAME_INCLUDE_DIR}/block)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_BLOCK_INCLUDE_DIR}/block.h
        ${MINECPP_GAME_BLOCK_INCLUDE_DIR}/color.h
        ${MINECPP_GAME_BLOCK_INCLUDE_DIR}/material.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/block.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/material.cpp
)