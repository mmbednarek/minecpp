set(MINECPP_CHAT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_chat STATIC)

# Public include headers
target_include_directories(minecpp_chat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_chat
        LINK_PUBLIC
        minecpp_format
        LINK_PRIVATE
        minecpp_utils
        fmt
)
