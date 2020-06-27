#include <gtest/gtest.h>
#include <game/blocks/position.h>
#include <iostream>

TEST(Block, Position) {
   Game::Block::Position p(-78, 20, -567);
   auto encoded = p.as_long();
   Game::Block::Position decoded(encoded);

   EXPECT_EQ(p.x, decoded.x);
   EXPECT_EQ(p.y, decoded.y);
   EXPECT_EQ(p.z, decoded.z);

   EXPECT_EQ(p.offset(), 10516);

   Game::Block::Position border(-16, 0, 0);
   EXPECT_EQ(border.offset(), 0);
   EXPECT_EQ(border.chunk_pos().x, -1);
}
