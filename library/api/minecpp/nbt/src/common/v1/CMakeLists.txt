set(MINECPP_API_MINECPP_NBT_COMMON_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_NBT_DIR}/include/minecpp/nbt/common/v1)
target_sources(minecpp_api_nbt PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Common.nbt.cpp

        # Header files
        ${MINECPP_API_MINECPP_NBT_COMMON_V1_INCLUDE_DIR}/Common.nbt.h
)

