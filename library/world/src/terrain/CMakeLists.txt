set(MINECPP_WORLD_TERRAIN_INCLUDE_DIR ${MINECPP_WORLD_DIR}/include/minecpp/world/terrain)

target_sources(minecpp_world PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Height.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Terrain.cpp

        # Header files
        ${MINECPP_WORLD_TERRAIN_INCLUDE_DIR}/Height.h
        ${MINECPP_WORLD_TERRAIN_INCLUDE_DIR}/Terrain.h
)

# Subdirectories

