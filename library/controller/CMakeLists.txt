add_library(minecpp_controller)
add_subdirectory("src")

target_link_libraries(minecpp_controller
        LINK_PUBLIC
        minecpp_game
        minecpp_repository
)
