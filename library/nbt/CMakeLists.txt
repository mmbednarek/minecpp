add_library(minecpp_nbt Exception.cpp Reader.cpp Writer.cpp Tag.cpp Parser.cpp)
target_link_libraries(minecpp_nbt LINK_PUBLIC minecpp_utils)