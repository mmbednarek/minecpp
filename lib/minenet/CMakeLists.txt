add_library(minecpp_net msg/reader.cpp msg/writer.cpp msg/clientbound.cpp msg/chunk.cpp)
target_link_libraries(minecpp_net PUBLIC minecpp_nbt minecpp_game Boost::system)
