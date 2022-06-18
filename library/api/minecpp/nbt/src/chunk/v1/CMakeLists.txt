set(MINECPP_API_MINECPP_NBT_CHUNK_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_NBT_DIR}/include/minecpp/nbt/chunk/v1)
target_sources(minecpp_api_nbt PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Chunk.nbt.cpp

        # Header files
        ${MINECPP_API_MINECPP_NBT_CHUNK_V1_INCLUDE_DIR}/Chunk.nbt.h
)

