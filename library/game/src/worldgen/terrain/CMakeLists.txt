set(MINECPP_GAME_WORLDGEN_TERRAIN_INCLUDE_DIR ${MINECPP_GAME_DIR}/include/minecpp/game/worldgen/terrain)

target_sources(minecpp_game PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Height.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Terrain.cpp

        # Header files
        ${MINECPP_GAME_WORLDGEN_TERRAIN_INCLUDE_DIR}/Height.h
        ${MINECPP_GAME_WORLDGEN_TERRAIN_INCLUDE_DIR}/Terrain.h
)

# Subdirectories

