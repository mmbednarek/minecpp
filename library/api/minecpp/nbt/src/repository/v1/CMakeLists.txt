set(MINECPP_API_MINECPP_NBT_REPOSITORY_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_NBT_DIR}/include/minecpp/nbt/repository/v1)
target_sources(minecpp_api_nbt PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Codec.nbt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Repository.nbt.cpp

        # Header files
        ${MINECPP_API_MINECPP_NBT_REPOSITORY_V1_INCLUDE_DIR}/Codec.nbt.h
        ${MINECPP_API_MINECPP_NBT_REPOSITORY_V1_INCLUDE_DIR}/Repository.nbt.h
)

