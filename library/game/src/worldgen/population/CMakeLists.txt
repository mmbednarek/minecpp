set(MINECPP_GAME_WORLDGEN_POPULATION_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/game/worldgen/population)

target_sources(minecpp_game PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Chunk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Population.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Tree.cpp

        # Header files
        ${MINECPP_GAME_WORLDGEN_POPULATION_INCLUDE_DIR}/Chunk.h
        ${MINECPP_GAME_WORLDGEN_POPULATION_INCLUDE_DIR}/Object.h
        ${MINECPP_GAME_WORLDGEN_POPULATION_INCLUDE_DIR}/Population.h
        ${MINECPP_GAME_WORLDGEN_POPULATION_INCLUDE_DIR}/Tree.h
)

# Subdirectories

