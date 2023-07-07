#pragma once

#include "Section.h"

#include "minecpp/game/ChunkPosition.h"
#include "minecpp/nbt/chunk/Chunk.schema.h"
#include "minecpp/nbt/Reader.h"
#include "minecpp/nbt/Tag.h"
#include "minecpp/proto/chunk/Chunk.pb.h"

#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <string_view>

namespace minecpp::world {

using boost::uuids::uuid;
using HeightContainer = container::TightArray<int, 256, uint64_t, 9>;

class Chunk : public game::IBlockContainer
{
 public:
   Chunk();
   Chunk(int x, int z, const std::array<short, 256> &height_map);

   void read_from_proto(const minecpp::proto::chunk::Chunk &proto);
   void set_height_map(game::HeightType height_type, const std::array<short, 256> &height_map);

   void create_empty_section(int8_t sec);
   mb::emptyres set_block_at(const game::BlockPosition &position, game::BlockStateId state) override;
   mb::result<game::BlockStateId> block_at(const game::BlockPosition &position) override;
   mb::result<game::LightValue> light_value_at(game::LightType type,
                                               const game::BlockPosition &position) override;
   mb::emptyres set_light_value_at(game::LightType type, const game::BlockPosition &position,
                                   game::LightValue value) override;
   int height_at(int x, int z);
   void put_section(int8_t level, Section sec);
   std::array<short, 256> get_height_map();
   [[nodiscard]] int height_at(game::HeightType type, game::BlockPosition position) const;
   void set_height(game::HeightType type, game::BlockPosition position, int value);
   [[nodiscard]] std::size_t section_count();

   static int maximum_y()
   {
      return 256;
   }

   static int minimum_y()
   {
      return 0;
   }

   void set_full()
   {
      m_is_full = true;
   }

   [[nodiscard]] constexpr bool full() const
   {
      return m_is_full;
   }

   [[nodiscard]] mb::result<Section &> section(std::int8_t y)
   {
      if (not m_sections.contains(y))
         return mb::error("no such section");

      return m_sections.at(y);
   }

   bool add_player_reference(game::PlayerId player_id);
   void remove_player_reference(game::PlayerId player_id);

   [[nodiscard]] game::ChunkPosition position() const;

   static mb::result<std::unique_ptr<Chunk>> from_nbt(minecpp::nbt::chunk::Chunk &chunk) noexcept;
   minecpp::nbt::chunk::Chunk to_nbt() noexcept;
   static std::unique_ptr<Chunk> from_proto(const minecpp::proto::chunk::Chunk &proto);
   [[nodiscard]] minecpp::proto::chunk::Chunk to_proto() const;

 private:
   mb::result<Section &> section_from_y_level(int y);
   [[nodiscard]] HeightContainer &height_by_type(game::HeightType type);
   [[nodiscard]] const HeightContainer &height_by_type(game::HeightType type) const;

   game::ChunkPosition m_position{};
   bool m_is_full = false;
   std::array<int, 1024> m_biomes{};
   HeightContainer m_motion_blocking_height;
   HeightContainer m_world_surface_height;
   HeightContainer m_light_blocking_height;
   std::map<int8_t, Section> m_sections;
   std::set<game::PlayerId> m_player_references;
   std::mutex m_player_references_mutex;
};

}// namespace minecpp::world