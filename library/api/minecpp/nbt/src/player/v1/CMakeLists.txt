set(MINECPP_API_MINECPP_NBT_PLAYER_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_NBT_DIR}/include/minecpp/nbt/player/v1)
target_sources(minecpp_api_nbt PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Player.nbt.cpp

        # Header files
        ${MINECPP_API_MINECPP_NBT_PLAYER_V1_INCLUDE_DIR}/Player.nbt.h
)

