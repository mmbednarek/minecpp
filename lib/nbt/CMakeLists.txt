add_library(minecpp_nbt exception.cpp reader.cpp writer.cpp tag.h tag.cpp parser.cpp parser.h)
target_link_libraries(minecpp_nbt LINK_PUBLIC minecpp_utils)
