include(api.cmake)
add_library(minecpp_api_nbt ${nbt_api_sources})
target_link_libraries(minecpp_api_nbt LINK_PUBLIC minecpp_nbt libmb)
