#include <gtest/gtest.h>
#include <minecpp/game/BlockPosition.h>
#include <minecpp/game/ChunkPosition.h>
#include <minecpp/game/ChunkRange.h>

using minecpp::game::ChunkPosition;
using minecpp::game::ChunkRange;

void test_position(int x, int y, int z)
{
   minecpp::game::BlockPosition p(x, y, z);
   auto encoded = p.as_long();
   minecpp::game::BlockPosition decoded(encoded);

   EXPECT_EQ(p.x(), decoded.x());
   EXPECT_EQ(p.y(), decoded.y());
   EXPECT_EQ(p.z(), decoded.z());
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

TEST(Block, ChunkRangeTest)
{
   minecpp::game::ChunkRange range{
           {-2, -2},
           { 2,  2}
   };

   std::vector<ChunkPosition> values{};
   std::copy(range.begin(), range.end(), std::back_inserter(values));

   std::vector<ChunkPosition> expected_values{
           {-2, -2},
           {-1, -2},
           { 0, -2},
           { 1, -2},
           { 2, -2},
           {-2, -1},
           {-1, -1},
           { 0, -1},
           { 1, -1},
           { 2, -1},
           {-2,  0},
           {-1,  0},
           { 0,  0},
           { 1,  0},
           { 2,  0},
           {-2,  1},
           {-1,  1},
           { 0,  1},
           { 1,  1},
           { 2,  1},
           {-2,  2},
           {-1,  2},
           { 0,  2},
           { 1,  2},
           { 2,  2},
   };

   EXPECT_EQ(values, expected_values);
}
