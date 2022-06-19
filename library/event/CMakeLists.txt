set(MINECPP_EVENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_event STATIC)

# Public include headers
target_include_directories(minecpp_event PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_event
        LINK_PUBLIC
        minecpp_game
)
