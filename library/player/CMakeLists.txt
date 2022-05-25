add_library(minecpp_player player.cpp tracking.cpp)
target_link_libraries(minecpp_player PUBLIC minecpp_utils spdlog)