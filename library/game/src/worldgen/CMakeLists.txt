set(MINECPP_GAME_WORLDGEN_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/game/worldgen)

target_sources(minecpp_game PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Generator.cpp

        # Header files
        ${MINECPP_GAME_WORLDGEN_INCLUDE_DIR}/Generator.h
)

# Subdirectories
add_subdirectory("population")
add_subdirectory("terrain")

