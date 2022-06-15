SET(MINECPP_PLAYER_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/player)

add_library(minecpp_player
        ${MINECPP_PLAYER_INCLUDE_DIR}/Id.h
        ${MINECPP_PLAYER_INCLUDE_DIR}/Inventory.h
        ${MINECPP_PLAYER_INCLUDE_DIR}/Player.h
        ${MINECPP_PLAYER_INCLUDE_DIR}/Provider.hpp
        ${MINECPP_PLAYER_INCLUDE_DIR}/Tracking.h
        Player.cpp
        Tracking.cpp
        Inventory.cpp
)
target_link_libraries(minecpp_player PUBLIC minecpp_utils spdlog libmb)