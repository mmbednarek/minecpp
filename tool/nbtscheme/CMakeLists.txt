project(minecpp_nbtscheme)

add_executable(minecpp_nbtscheme main.cpp)
target_link_libraries(minecpp_nbtscheme LINK_PUBLIC minecpp_nbt minecpp_utils fmt)