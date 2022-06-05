SET(MINECPP_PLAYER_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/player)

add_library(minecpp_player
        ${MINECPP_PLAYER_INCLUDE_DIR}/id.h
        ${MINECPP_PLAYER_INCLUDE_DIR}/inventory.h
        ${MINECPP_PLAYER_INCLUDE_DIR}/player.h
        ${MINECPP_PLAYER_INCLUDE_DIR}/provider.hpp
        ${MINECPP_PLAYER_INCLUDE_DIR}/tracking.h
        player.cpp
        tracking.cpp
        inventory.cpp
)
target_link_libraries(minecpp_player PUBLIC minecpp_utils spdlog libmb)