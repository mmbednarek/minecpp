SET(MINECPP_GAME_ENTITY_INCLUDE_DIR ${MINECPP_GAME_INCLUDE_DIR}/entity)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_ENTITY_INCLUDE_DIR}/entity.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/entity.cpp
)