#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include <minecpp/container/PalettedVector.h>
#include <minecpp/container/TightArray.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/World.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <minecpp/squeezed/Tiny.h>
#include <minecpp/squeezed/Vector.h>
#include <vector>

namespace minecpp::world {

using LightContainer     = container::TightArray<game::LightValue, 4096, mb::u8, 4>;
using LightContainerUPtr = std::unique_ptr<LightContainer>;

struct Section final : public game::ISection
{
   int m_reference_count{};
   container::PalettedVector<game::BlockStateId> m_data;
   LightContainerUPtr m_block_light;
   LightContainerUPtr m_sky_light;
   std::vector<game::LightSource> m_light_sources;

   Section() = default;

   Section(int refCount, container::PalettedVector<game::BlockStateId> data,
           std::vector<game::LightSource> mLightSources);

   Section(const Section &section);
   Section &operator=(const Section &section);

   std::vector<game::LightSource> &light_sources() override;
   void reset_light(game::LightType light_type) override;

   static Section from_proto(const proto::chunk::v1::Section &section);
   [[nodiscard]] proto::chunk::v1::Section to_proto() const;

   void recalculate_reference_count();

   [[nodiscard]] constexpr const container::PalettedVector<game::BlockStateId> &data() const
   {
      return m_data;
   }

   [[nodiscard]] constexpr container::PalettedVector<game::BlockStateId> &data()
   {
      return m_data;
   }

   [[nodiscard]] constexpr int reference_count() const
   {
      return m_reference_count;
   }

   [[nodiscard]] game::LightValue get_light(game::LightType type, game::BlockPosition position)
   {
      return light_data(type).at(position.section_offset());
   }

   [[nodiscard]] void set_light(game::LightType type, game::BlockPosition position, game::LightValue value)
   {
      light_data(type).set(position.section_offset(), value);
   }

   [[nodiscard]] game::BlockStateId get_block(game::BlockPosition position) const
   {
      return m_data.at(position.section_offset());
   }

   [[nodiscard]] LightContainer &light_data(game::LightType type)
   {
      switch (type) {
      case game::LightType::Block:
         if (m_block_light == nullptr) {
            m_block_light = std::make_unique<LightContainer>();
         }
         return *m_block_light;
      case game::LightType::Sky:
         if (m_sky_light == nullptr) {
            m_sky_light = std::make_unique<LightContainer>();
         }
         return *m_sky_light;
      }
      assert(false && "NON REACHABLE");
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