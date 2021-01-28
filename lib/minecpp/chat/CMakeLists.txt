add_library(minecpp_chat parser.cpp ../error/error.cpp)
target_link_libraries(minecpp_chat LINK_PUBLIC minecpp_utils)
