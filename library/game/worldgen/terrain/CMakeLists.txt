SET(MINECPP_GAME_WORLDGEN_TERRAIN_INCLUDE_DIR ${MINECPP_GAME_WORLDGEN_INCLUDE_DIR}/terrain)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_WORLDGEN_TERRAIN_INCLUDE_DIR}/Height.h
        ${MINECPP_GAME_WORLDGEN_TERRAIN_INCLUDE_DIR}/Terrain.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Height.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Terrain.cpp
)