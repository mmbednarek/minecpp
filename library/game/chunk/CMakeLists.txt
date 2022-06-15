SET(MINECPP_GAME_CHUNK_INCLUDE_DIR ${MINECPP_GAME_INCLUDE_DIR}/chunk)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_CHUNK_INCLUDE_DIR}/chunk.h
        ${MINECPP_GAME_CHUNK_INCLUDE_DIR}/section.h
        ${MINECPP_GAME_CHUNK_INCLUDE_DIR}/utils.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/chunk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/section.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
)