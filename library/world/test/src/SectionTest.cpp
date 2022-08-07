#include <gtest/gtest.h>
#include <minecpp/world/Section.h>

using minecpp::container::PalettedVector;
using minecpp::game::BlockStateId;
using minecpp::world::Section;

TEST(Section, ProtoTest)
{
   std::vector<BlockStateId> ids;
   ids.resize(4096);
   for (std::size_t i{0}; i < 4096; ++i) {
      ids[i] = i % 22;
   }

   Section section{};
   section.block_light.fill(4096, 1);
   section.sky_light.fill(4096, 2);
   section.m_data = {ids.begin(), ids.end()};

   auto proto = section.to_proto();

   ASSERT_EQ(proto.sky_light().size(), 4096);

   auto decoded_section = Section::from_proto(proto);

   ASSERT_EQ(decoded_section.data().palette().size(), section.data().palette().size());
   for (std::size_t i{0}; i < decoded_section.data().palette().size(); ++i) {
      ASSERT_EQ(decoded_section.data().palette()[i], section.data().palette()[i]);
   }

   ASSERT_EQ(decoded_section.data().size(), 4096);
   for (std::size_t i{0}; i < 4096; ++i) {
      ASSERT_EQ(decoded_section.m_data[i], section.m_data[i]);
   }
}