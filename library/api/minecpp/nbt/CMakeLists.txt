set(MINECPP_API_MINECPP_NBT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_api_nbt STATIC)

# Public include headers
target_include_directories(minecpp_api_nbt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_api_nbt
        LINK_PUBLIC
        minecpp_nbt
        libmb
)
