set(MINECPP_GAME_ENTITY_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/game/entity)

target_sources(minecpp_game PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp

        # Header files
        ${MINECPP_GAME_ENTITY_INCLUDE_DIR}/Entity.h
)

# Subdirectories

