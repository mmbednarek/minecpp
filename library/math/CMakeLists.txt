# THIS FILE HAS BEEN GENERATED BY THE BUILD CONFIGURATION SYSTEM - DO NOT EDIT

set(MINECPP_MATH_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_math INTERFACE)

# Public include headers
target_include_directories(minecpp_math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(minecpp_math
        INTERFACE
        fmt::fmt
)

add_subdirectory("test")
