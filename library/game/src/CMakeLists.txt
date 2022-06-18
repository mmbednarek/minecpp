set(MINECPP_GAME_INCLUDE_DIR ${MINECPP_GAME_DIR}/include/minecpp/game)

target_sources(minecpp_game PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Rules.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World.cpp

        # Header files
        ${MINECPP_GAME_INCLUDE_DIR}/EntityManager.hpp
        ${MINECPP_GAME_INCLUDE_DIR}/Game.h
        ${MINECPP_GAME_INCLUDE_DIR}/Hand.h
        ${MINECPP_GAME_INCLUDE_DIR}/Mode.h
        ${MINECPP_GAME_INCLUDE_DIR}/Notifier.h
        ${MINECPP_GAME_INCLUDE_DIR}/Rules.h
        ${MINECPP_GAME_INCLUDE_DIR}/State.h
        ${MINECPP_GAME_INCLUDE_DIR}/World.h
)

# Subdirectories
add_subdirectory("block")
add_subdirectory("entity")
add_subdirectory("item")
add_subdirectory("player")

