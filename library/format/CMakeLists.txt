set(MINECPP_FORMAT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_format)

# Public include headers
target_include_directories(minecpp_format PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_format
)
