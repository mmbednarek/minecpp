project(minecpp_message_nbt)

add_library(minecpp_message_nbt chunk.nbt.cpp level.nbt.cpp)
target_link_libraries(minecpp_message_nbt PUBLIC minecpp_nbt libmb)