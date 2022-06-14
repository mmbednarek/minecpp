SET(MINECPP_GAME_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/game)

add_library(minecpp_game
        rules.cpp
        item/recipe.cpp
        item/item.cpp
        chunk/chunk.cpp
        chunk/utils.cpp
        block/block.cpp
        block/material.cpp
        block/block.cpp
        entity/entity.cpp
        world.cpp
        worldgen/terrain/terrain.cpp
        chunk/section.cpp
        worldgen/terrain/height.cpp
        worldgen/population/object.cpp
        worldgen/population/population.cpp
        worldgen/population/chunk.cpp
        worldgen/generator.cpp
        worldgen/population/tree.cpp
        # Header files
        ${MINECPP_GAME_INCLUDE_DIR}/state.h
        )

target_link_libraries(minecpp_game LINK_PUBLIC minecpp_utils minecpp_nbt minecpp_api_nbt minecpp_error minecpp_squeeze spdlog ${Protobuf_LIBRARIES} grpc++)
