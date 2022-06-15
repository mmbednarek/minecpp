SET(MINECPP_GAME_CONTROLLER_INCLUDE_DIR ${MINECPP_GAME_INCLUDE_DIR}/controller)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_CONTROLLER_INCLUDE_DIR}/BlockController.hpp
        ${MINECPP_GAME_CONTROLLER_INCLUDE_DIR}/BlockManager.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/BlockManager.cpp
)

add_subdirectory("block")
