project(minecpp_nbt_viewer)

add_executable(minecpp_nbt_viewer main.cpp)
target_link_libraries(minecpp_nbt_viewer LINK_PUBLIC minecpp_nbt minecpp_utils fmt)
