set(MINECPP_GAME_CHUNK_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/game/chunk)

target_sources(minecpp_game PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Chunk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Section.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp

        # Header files
        ${MINECPP_GAME_CHUNK_INCLUDE_DIR}/Chunk.h
        ${MINECPP_GAME_CHUNK_INCLUDE_DIR}/Section.h
        ${MINECPP_GAME_CHUNK_INCLUDE_DIR}/Utils.h
)

# Subdirectories

