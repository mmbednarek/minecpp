add_library(minecpp_net message/reader.cpp message/writer.cpp message/clientbound.cpp message/chunk.cpp message/serverbound.cpp chat.cpp)
target_link_libraries(minecpp_net PUBLIC minecpp_nbt minecpp_game Boost::system)
