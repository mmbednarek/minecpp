#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include <minecpp/container/PalettedVector.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/World.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <minecpp/squeezed/Tiny.h>
#include <minecpp/squeezed/Vector.h>
#include <vector>

namespace minecpp::world {

struct Section final : public game::ISection
{
   int m_reference_count{};
   container::PalettedVector<game::BlockStateId> m_data;
   squeezed::TinyVec<4> block_light;
   squeezed::TinyVec<4> sky_light;
   std::vector<game::LightSource> m_light_sources;

   Section() = default;

   Section(int refCount, container::PalettedVector<game::BlockStateId> data, squeezed::TinyVec<4> blockLight,
           squeezed::TinyVec<4> skyLight, std::vector<game::LightSource> mLightSources);

   std::vector<game::LightSource> &light_sources() override;
   void reset_light(game::LightType light_type) override;

   static Section from_proto(const proto::chunk::v1::Section &section);
   proto::chunk::v1::Section to_proto() const;

   void recalculate_reference_count();

   [[nodiscard]] constexpr const container::PalettedVector<game::BlockStateId> &data() const
   {
      return m_data;
   }

   [[nodiscard]] constexpr container::PalettedVector<game::BlockStateId> &data()
   {
      return m_data;
   }
};

class SectionBuilder
{
   std::array<game::BlockStateId, 4096> content{};

 public:
   SectionBuilder();

   void fill(std::function<int(short, short, short)> callback);
   Section build();
};

}// namespace minecpp::world