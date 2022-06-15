SET(MINECPP_GAME_ITEM_INCLUDE_DIR ${MINECPP_GAME_INCLUDE_DIR}/item)

target_sources(minecpp_game PRIVATE
        # Header files
        ${MINECPP_GAME_ITEM_INCLUDE_DIR}/Item.h
        ${MINECPP_GAME_ITEM_INCLUDE_DIR}/Recipe.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Item.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Recipe.cpp
)