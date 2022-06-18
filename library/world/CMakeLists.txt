set(MINECPP_WORLD_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_world)

# Public include headers
target_include_directories(minecpp_world PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_world
        LINK_PUBLIC
        minecpp_game
        minecpp_repository
)
