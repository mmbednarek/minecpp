add_library(minecpp_nbt parser.cpp tag.cpp exception.cpp snbt.cpp reader.cpp compound_map.cpp compound_map.h writer.cpp)
target_link_libraries(minecpp_nbt LINK_PUBLIC minecpp_utils)
