#include <gtest/gtest.h>
#include <minecpp/world/Section.h>

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
   section.fill_light(minecpp::game::LightType::Block);
   section.fill_light(minecpp::game::LightType::Sky);
   section.data() = {ids.begin(), ids.end()};

   auto proto = section.to_proto();

   ASSERT_EQ(proto.sky_light().size(), 4096);

   auto decoded_section = Section::from_proto(proto);

   ASSERT_EQ(decoded_section.data().palette().size(), section.data().palette().size());
   for (std::size_t i{0}; i < decoded_section.data().palette().size(); ++i) {
      ASSERT_EQ(decoded_section.data().palette()[i], section.data().palette()[i]);
   }

   ASSERT_EQ(decoded_section.data().size(), 4096);
   for (std::size_t i{0}; i < 4096; ++i) {
      ASSERT_EQ(decoded_section.data()[i], section.data()[i]);
   }
}
