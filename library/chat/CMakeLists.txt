add_library(minecpp_chat Parser.cpp ../error/Error.cpp Chat.cpp)
target_link_libraries(minecpp_chat LINK_PUBLIC minecpp_utils fmt)
