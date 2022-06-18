set(MINECPP_GAME_PLAYER_INCLUDE_DIR ${MINECPP_GAME_DIR}/include/minecpp/game/player)
target_sources(minecpp_game PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Inventory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Tracking.cpp

        # Header files
        ${MINECPP_GAME_PLAYER_INCLUDE_DIR}/Id.h
        ${MINECPP_GAME_PLAYER_INCLUDE_DIR}/Inventory.h
        ${MINECPP_GAME_PLAYER_INCLUDE_DIR}/Player.h
        ${MINECPP_GAME_PLAYER_INCLUDE_DIR}/Provider.hpp
        ${MINECPP_GAME_PLAYER_INCLUDE_DIR}/Tracking.h
)

