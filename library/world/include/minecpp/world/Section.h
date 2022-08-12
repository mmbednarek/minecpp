#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include <minecpp/container/PalettedVector.h>
#include <minecpp/container/TightArray.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/World.h>
#include <minecpp/nbt/chunk/v1/Chunk.nbt.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <minecpp/squeezed/Tiny.h>
#include <minecpp/squeezed/Vector.h>
#include <vector>

namespace minecpp::world {

using LightContainer     = container::TightArray<game::LightValue, 4096, mb::u8, 4>;
using LightContainerUPtr = std::unique_ptr<LightContainer>;

class Section final : public game::ISection
{
 public:
   Section(int y);

   Section(int refCount, container::PalettedVector<game::BlockStateId> data,
           std::vector<game::LightSource> mLightSources);

   Section(const Section &section);
   Section &operator=(const Section &section);

   std::vector<game::LightSource> &light_sources() override;
   void reset_light(game::LightType light_type) override;

   [[nodiscard]] static Section from_proto(const proto::chunk::v1::Section &section);
   [[nodiscard]] proto::chunk::v1::Section to_proto() const;

   [[nodiscard]] static Section from_nbt(const nbt::chunk::v1::Section &section);
   [[nodiscard]] nbt::chunk::v1::Section to_nbt() const;

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

   [[nodiscard]] game::LightValue get_light(game::LightType type, game::BlockPosition position) const
   {
      const auto* light = light_data(type);
      if (light == nullptr)
         return 0;
      return light->at(position.section_offset());
   }

   [[nodiscard]] void set_light(game::LightType type, game::BlockPosition position, game::LightValue value)
   {
      auto* light = light_data(type);
      if (light == nullptr) {
         fill_light(type);
         light = light_data(type);
      }
      light->set(position.section_offset(), value);
   }

   [[nodiscard]] game::BlockStateId get_block(game::BlockPosition position) const
   {
      return m_data.at(position.section_offset());
   }

   void set_block(game::BlockPosition position, game::BlockStateId id);

   void fill_light(game::LightType type) {
      switch (type) {
      case game::LightType::Block:
         m_block_light = std::make_unique<LightContainer>();
         break;
      case game::LightType::Sky:
         m_sky_light = std::make_unique<LightContainer>();
         break;
      }
   }

   [[nodiscard]] LightContainer *light_data(game::LightType type) const
   {
      switch (type) {
      case game::LightType::Block: return m_block_light.get();
      case game::LightType::Sky: return m_sky_light.get();
      }
      return nullptr;
   }

 private:
   int m_reference_count{};
   int m_y{};
   container::PalettedVector<game::BlockStateId> m_data;
   LightContainerUPtr m_block_light;
   LightContainerUPtr m_sky_light;
   std::vector<game::LightSource> m_light_sources;
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