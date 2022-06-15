SET(MINECPP_GAME_WORLDGEN_TERRAIN_INCLUDE_DIR ${MINECPP_GAME_WORLDGEN_INCLUDE_DIR}/terrain)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_WORLDGEN_TERRAIN_INCLUDE_DIR}/height.h
        ${MINECPP_GAME_WORLDGEN_TERRAIN_INCLUDE_DIR}/terrain.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/height.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/terrain.cpp
)