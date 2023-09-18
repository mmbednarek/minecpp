#include <gtest/gtest.h>

#include "minecpp/repository/Repository.h"
#include "minecpp/world/Chunk.h"
#include "minecpp/world/ChunkSerializer.h"
#include "minecpp/world/Section.h"

using minecpp::game::BlockStateId;
using minecpp::world::Chunk;
using minecpp::world::Section;

class SectionTest : public ::testing::Test
{
 protected:
   void SetUp() override
   {
      static bool g_initialised_repository = false;
      if (not g_initialised_repository) {
         ASSERT_TRUE(minecpp::repository::load_repository_from_file("repository.bin").ok());
         g_initialised_repository = true;
      }
   }

   void TearDown() override {}
};

TEST_F(SectionTest, ProtoTest)
{
   std::vector<BlockStateId> ids;
   ids.resize(4096);
   for (BlockStateId i{0}; i < 4096; ++i) {
      ids[i] = i % 22;
   }

   std::array<short, 256> heightmap{};
   Chunk chunk(0, 0, heightmap);

   int count = 0;

   for (int y = 0; y < 80; ++y) {
      int section = y / 16;
      for (int x = 0; x < 16; ++x) {
         for (int z = 0; z < 16; ++z) {
            if (y < 64) {
               int block_id = (section == 0) ? 1 : (count % (1 << (section + 1)));
               ASSERT_TRUE(chunk.set_block_at({x, y, z}, static_cast<BlockStateId>(block_id)).ok());
            } else {
               ASSERT_TRUE(chunk.set_light_value_at(minecpp::game::LightType::Sky, {x, y, z}, 16).ok());
            }
            ++count;
         }
      }
   }

   ASSERT_EQ(chunk.section_count(), 5);

   minecpp::world::ChunkSerializer chunk_serializer{chunk};

   minecpp::net::Chunk out_chunk;
   chunk_serializer.write_chunk(out_chunk);

   Chunk chunk2(0, 0, heightmap);
   chunk2.read_net_chunk(out_chunk);

   ASSERT_EQ(chunk2.section_count(), 5);

   for (int y = 0; y < 80; ++y) {
      for (int x = 0; x < 16; ++x) {
         for (int z = 0; z < 16; ++z) {
            auto block_id = chunk.block_at({x, y, z});
            ASSERT_TRUE(block_id.ok());

            auto block_id2 = chunk2.block_at({x, y, z});
            ASSERT_TRUE(block_id2.ok());

            ASSERT_EQ(*block_id, *block_id2);

            auto block_val = chunk.light_value_at(minecpp::game::LightType::Sky, {x, y, z});
            ASSERT_TRUE(block_val.ok());

            auto block_val2 = chunk2.light_value_at(minecpp::game::LightType::Sky, {x, y, z});
            ASSERT_TRUE(block_val2.ok());

            ASSERT_EQ(*block_val, *block_val2);
         }
      }
   }
}
