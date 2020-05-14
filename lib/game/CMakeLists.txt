add_library(minecpp_game rules.cpp level/level.cpp chunk/chunk.cpp level/dimension.h recipe.cpp recipe.h)
target_link_libraries(minecpp_game LINK_PUBLIC minecpp_utils minecpp_nbt)
