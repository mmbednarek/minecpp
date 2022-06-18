set(MINECPP_GAME_BLOCK_INCLUDE_DIR ${MINECPP_GAME_DIR}/include/minecpp/game/block)
target_sources(minecpp_game PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Material.cpp

        # Header files
        ${MINECPP_GAME_BLOCK_INCLUDE_DIR}/Block.h
        ${MINECPP_GAME_BLOCK_INCLUDE_DIR}/Color.h
        ${MINECPP_GAME_BLOCK_INCLUDE_DIR}/Material.h
)

