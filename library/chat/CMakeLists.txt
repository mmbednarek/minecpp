add_library(minecpp_chat Parser.cpp Chat.cpp)
target_link_libraries(minecpp_chat LINK_PUBLIC minecpp_utils minecpp_format fmt)
