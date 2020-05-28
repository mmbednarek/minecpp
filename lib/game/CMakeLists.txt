add_library(minecpp_game rules.cpp level/level.cpp chunk/chunk.cpp level/dimension.h items/recipe.cpp items/item.cpp items/registry.cpp items/registry.h chunk/section.cpp chunk/section.h)
target_link_libraries(minecpp_game LINK_PUBLIC minecpp_utils minecpp_nbt)
