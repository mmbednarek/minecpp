SET(MINECPP_GAME_CHUNK_INCLUDE_DIR ${MINECPP_GAME_INCLUDE_DIR}/chunk)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_CHUNK_INCLUDE_DIR}/Chunk.h
        ${MINECPP_GAME_CHUNK_INCLUDE_DIR}/Section.h
        ${MINECPP_GAME_CHUNK_INCLUDE_DIR}/Utils.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Chunk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Section.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
)