set(MINECPP_API_MINECPP_NBT_LEVEL_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_NBT_DIR}/include/minecpp/nbt/level/v1)
target_sources(minecpp_api_nbt PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Level.nbt.cpp

        # Header files
        ${MINECPP_API_MINECPP_NBT_LEVEL_V1_INCLUDE_DIR}/Level.nbt.h
)

