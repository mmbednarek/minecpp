add_library(minecpp_net message/Reader.cpp message/Writer.cpp message/Clientbound.cpp message/Chunk.cpp message/Serverbound.cpp Chat.cpp)
target_link_libraries(minecpp_net PUBLIC minecpp_nbt minecpp_game Boost::system)
