#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include <minecpp/container/PalettedVector.h>
#include <minecpp/container/TightArray.h>
#include <minecpp/game/IWorld.hpp>
#include <minecpp/nbt/chunk/Chunk.schema.h>
#include <minecpp/proto/chunk/Chunk.pb.h>
#include <shared_mutex>
#include <vector>

namespace minecpp::world {

using LightContainer     = container::TightArray<game::LightValue, 4096, mb::u8, 4>;
using LightContainerUPtr = std::unique_ptr<LightContainer>;

class Section final : public game::ISection
{
 public:
   explicit Section(int y);

   Section(int ref_count, container::PalettedVector<game::BlockStateId> data,
           std::vector<game::LightSource> light_sources);

   Section(const Section &section);
   Section &operator=(const Section &section);

   std::vector<game::LightSource> &light_sources() override;
   void reset_light(game::LightType light_type) override;

   [[nodiscard]] static Section from_proto(const proto::chunk::Section &section);
   [[nodiscard]] proto::chunk::Section to_proto() const;

   [[nodiscard]] static Section from_nbt(const nbt::chunk::Section &section);
   [[nodiscard]] nbt::chunk::Section to_nbt() const;

   void recalculate_reference_count();

   [[nodiscard]] const container::PalettedVector<game::BlockStateId> &data() const;

   [[nodiscard]] constexpr container::PalettedVector<game::BlockStateId> &data()
   {
      // TODO: MUTEX!!!
      return m_data;
   }

   [[nodiscard]] int reference_count() const;

   [[nodiscard]] game::LightValue get_light(game::LightType type, game::BlockPosition position) const;

   void set_light(game::LightType type, game::BlockPosition position, game::LightValue value);

   [[nodiscard]] game::BlockStateId get_block(game::BlockPosition position) const;

   void set_block(game::BlockPosition position, game::BlockStateId id);

   void fill_light(game::LightType type);

   [[nodiscard]] LightContainer *light_data(game::LightType type) const;

 private:
   [[nodiscard]] game::BlockStateId get_block_internal(game::BlockPosition position) const;
   [[nodiscard]] LightContainer *light_data_internal(game::LightType type) const;
   void fill_light_internal(game::LightType type);

   int m_reference_count{};
   int m_y{};
   container::PalettedVector<game::BlockStateId> m_data;
   LightContainerUPtr m_block_light;
   LightContainerUPtr m_sky_light;
   std::vector<game::LightSource> m_light_sources;

   mutable std::shared_mutex m_mutex;
};

class SectionBuilder
{
   std::array<game::BlockStateId, 4096> m_content{};

 public:
   SectionBuilder();

   void fill(const std::function<int(short, short, short)> &callback);
   Section build();
};

}// namespace minecpp::world