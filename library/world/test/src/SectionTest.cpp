#include <gtest/gtest.h>

#include "minecpp/world/Chunk.h"
#include "minecpp/world/ChunkSerializer.h"
#include "minecpp/world/Section.h"

using minecpp::game::BlockStateId;
using minecpp::world::Chunk;
using minecpp::world::Section;

TEST(Section, ProtoTest)
{
   std::vector<BlockStateId> ids;
   ids.resize(4096);
   for (BlockStateId i{0}; i < 4096; ++i) {
      ids[i] = i % 22;
   }

   std::array<short, 256> heightmap{};
   Chunk chunk(0, 0, heightmap);
   chunk.create_empty_section(0);

   chunk.set_block_at({5, 5, 5}, 1);
   chunk.set_block_at({5, 5, 6}, 1);

   minecpp::world::ChunkSerializer chunk_serializer{chunk};

   minecpp::net::Chunk out_chunk;
   chunk_serializer.write_chunk(out_chunk);

   Section section{1};
   section.fill_light(minecpp::game::LightType::Block);
   section.fill_light(minecpp::game::LightType::Sky);
   section.data() = {ids.begin(), ids.end()};

   //   ASSERT_EQ(proto.sky_light().size(), 2048);
   //
   //   auto decoded_section = Section::from_proto(proto);
   //
   //   ASSERT_EQ(decoded_section.data().palette().size(), section.data().palette().size());
   //   for (std::size_t i{0}; i < decoded_section.data().palette().size(); ++i) {
   //      ASSERT_EQ(decoded_section.data().palette()[i], section.data().palette()[i]);
   //   }
   //
   //   ASSERT_EQ(decoded_section.data().size(), 4096);
   //   for (std::size_t i{0}; i < 4096; ++i) {
   //      ASSERT_EQ(decoded_section.data()[i], section.data()[i]);
   //   }
}
