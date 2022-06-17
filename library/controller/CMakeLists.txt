set(MINECPP_CONTROLLER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_controller)

# Public include headers
target_include_directories(minecpp_controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_controller
        LINK_PUBLIC
        minecpp_game
        minecpp_repository
)
