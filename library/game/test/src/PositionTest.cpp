#include "minecpp/game/Game.h"
#include <gtest/gtest.h>

void test_position(int x, int y, int z)
{
   minecpp::game::BlockPosition p(x, y, z);
   auto encoded = p.as_long();
   minecpp::game::BlockPosition decoded(encoded);

   EXPECT_EQ(p.x, decoded.x);
   EXPECT_EQ(p.y, decoded.y);
   EXPECT_EQ(p.z, decoded.z);
}

TEST(Block, Position)
{
   test_position(100, 60, 100);
   test_position(-100, 60, 100);
   test_position(100, 60, -200);
   test_position(100, -60, -200);
   test_position(-100, -60, -200);

   minecpp::game::BlockPosition p(-78, 20, -567);

   EXPECT_EQ(p.offset(), 10516);

   minecpp::game::BlockPosition border(-16, 0, 0);
   EXPECT_EQ(border.offset(), 0);
   EXPECT_EQ(border.chunk_position().x(), -1);
}
