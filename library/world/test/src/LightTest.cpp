#include <fmt/core.h>
#include <gtest/gtest.h>
#include <minecpp/repository/Repository.h>
#include <minecpp/world/BlockState.h>
#include <minecpp/world/LightSystem.h>
#include <minecpp/world/testing/BlockContainer.h>

using minecpp::game::BlockRange;
using minecpp::world::BlockState;
using minecpp::world::LightSystem;
using minecpp::world::testing::BlockContainer;

bool g_initialised_repository{false};

class WorldLightTest : public ::testing::Test
{
 protected:
   void SetUp() override
   {
      if (not g_initialised_repository) {
         ASSERT_TRUE(minecpp::repository::load_repository_from_file("repository.bin").ok());
         g_initialised_repository = true;
      }
   }

   void TearDown() override {}
};

TEST_F(WorldLightTest, LightTest_MinorLightSource)
{
   BlockContainer container({
           {-15, -15, -15},
           { 15,  15,  15}
   });

   LightSystem light_system(container);
   light_system.add_light_source({0, 0, 0}, 3);
   ASSERT_EQ(container.light_changes(), 25);
}

TEST_F(WorldLightTest, LightTest_MaxValueSource)
{
   BlockContainer container({
           {-20, -20, -20},
           { 20,  20,  20}
   });

   LightSystem light_system(container);
   light_system.add_light_source({0, 0, 0}, 15);
   ASSERT_EQ(container.light_changes(), 4089);
}

TEST_F(WorldLightTest, LightTest_ResetLight)
{
   BlockContainer container({
           {-20, -20, -20},
           { 20,  20,  20}
   });

   LightSystem light_system(container);
   light_system.add_light_source({0, 0, 0}, 3);
   ASSERT_EQ(container.light_changes(), 25);
   light_system.reset_light(minecpp::game::LightType::Block, {0, 0, 0});
   ASSERT_EQ(container.light_changes(), 50);
}

TEST_F(WorldLightTest, LightTest_Range)
{
   BlockRange range{
           {-1, -1, -1},
           { 1,  1,  1}
   };
   int count{};
   for (auto pos : range) {
      fmt::print("position: {}, {}, {}\n", pos.x(), pos.y(), pos.z());
      ++count;
   }
   ASSERT_EQ(count, 27);
}

TEST_F(WorldLightTest, LightTest_Box)
{
   BlockContainer container({
           {-15, -15, -15},
           { 15,  15,  15}
   });
   BlockRange box_range{
           {-2, -2, -2},
           { 2,  2,  2}
   };
   container.put_box(box_range, DEFAULT_BLOCK_STATE(Stone));

   /*
   world::StructureHelper helper{container};
   helper.apply_shape(world::BoxShape{
      {-2, -2, -2},
      { 2,  2,  2}), DEFAULT_BLOCK_STATE(Stone));
   */

   LightSystem light_system(container);
   light_system.add_light_source({0, 0, 0}, 15);
   ASSERT_EQ(container.light_changes(), 27);
}

TEST_F(WorldLightTest, LightTest_BoxWithAHole)
{
   BlockContainer container({
           {-15, -15, -15},
           { 15,  15,  15}
   });
   BlockRange box_range{
           {-2, -2, -2},
           { 2,  2,  2}
   };
   container.put_box(box_range, DEFAULT_BLOCK_STATE(Stone));
   container.set_block_at({2, 0, 0}, DEFAULT_BLOCK_STATE(Air));

   /*
   world::StructureHelper helper{container};
   helper.apply_shape(world::BoxShape{
      {-2, -2, -2},
      { 2,  2,  2}), DEFAULT_BLOCK_STATE(Stone));
   */
   static constexpr auto expected_changes{27 + 1 + 2047 - 125 - 90 + 20};

   LightSystem light_system(container);
   light_system.add_light_source({0, 0, 0}, 15);
   ASSERT_EQ(container.light_changes(), expected_changes);
   light_system.reset_light(minecpp::game::LightType::Block, {0, 0, 0});
   ASSERT_EQ(container.light_changes(), 2 * expected_changes);
}
