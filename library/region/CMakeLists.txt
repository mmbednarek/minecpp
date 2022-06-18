set(MINECPP_REGION_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_region STATIC)

# Public include headers
target_include_directories(minecpp_region PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_region
        LINK_PUBLIC
        Boost::iostreams
        libmb
        fmt
        LINK_PRIVATE
        minecpp_utils
)
