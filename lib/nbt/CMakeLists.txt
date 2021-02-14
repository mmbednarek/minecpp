add_library(minecpp_nbt exception.cpp reader.cpp writer.cpp tag.cpp parser.cpp)
target_link_libraries(minecpp_nbt LINK_PUBLIC minecpp_utils minecpp_error)
