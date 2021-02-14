#include <gtest/gtest.h>
#include <iostream>
#include <minecpp/game/block/position.h>

TEST(Block, Position) {
   minecpp::game::block::Position p(-78, 20, -567);
   auto encoded = p.as_long();
   minecpp::game::block::Position decoded(encoded);

   EXPECT_EQ(p.x, decoded.x);
   EXPECT_EQ(p.y, decoded.y);
   EXPECT_EQ(p.z, decoded.z);

   EXPECT_EQ(p.offset(), 10516);

   minecpp::game::block::Position border(-16, 0, 0);
   EXPECT_EQ(border.offset(), 0);
   EXPECT_EQ(border.chunk_pos().x, -1);
}
