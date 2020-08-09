add_library(minecpp_chat parser.cpp ../error/error.cpp ../error/error.h)
target_link_libraries(minecpp_chat LINK_PUBLIC minecpp_utils)
