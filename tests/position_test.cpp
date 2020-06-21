#include <gtest/gtest.h>
#include <game/blocks/position.h>

TEST(Block, Position) {
   Game::Block::Position p(-78, 20, -567);
   auto encoded = p.as_long();
   Game::Block::Position decoded(encoded);

   EXPECT_EQ(p.x, decoded.x);
   EXPECT_EQ(p.y, decoded.y);
   EXPECT_EQ(p.z, decoded.z);
}
