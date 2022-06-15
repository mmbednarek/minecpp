SET(MINECPP_GAME_WORLDGEN_INCLUDE_DIR ${MINECPP_GAME_INCLUDE_DIR}/worldgen)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_WORLDGEN_INCLUDE_DIR}/generator.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp
)

add_subdirectory("population")
add_subdirectory("terrain")
