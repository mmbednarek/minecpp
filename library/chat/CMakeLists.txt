add_library(minecpp_chat parser.cpp ../error/error.cpp chat.cpp)
target_link_libraries(minecpp_chat LINK_PUBLIC minecpp_utils fmt)
