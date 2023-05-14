#ifndef MINECPP_GAME_CHUNK_CHUNK_H
#define MINECPP_GAME_CHUNK_CHUNK_H

#include "Section.h"
#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <minecpp/nbt/chunk/v1/Chunk.nbt.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Tag.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <string_view>

namespace minecpp::world {

using boost::uuids::uuid;
using HeightContainer = container::TightArray<int, 256, uint64_t, 9>;

class Chunk : public game::IBlockContainer
{
 public:
   Chunk();
   Chunk(int x, int z, const std::array<short, 256> &height_map);

   void as_proto(minecpp::proto::chunk::v1::Chunk *chunk);
   [[nodiscard]] minecpp::proto::chunk::v1::Chunk to_proto() const;
   static Chunk from_proto(const minecpp::proto::chunk::v1::Chunk &proto);
   void read_from_proto(const minecpp::proto::chunk::v1::Chunk &proto);
   void set_height_map(game::HeightType height_type, const std::array<short, 256> &height_map);

   void create_empty_section(int8_t sec);
   mb::emptyres set_block(const game::BlockPosition &position, game::BlockStateId state) override;
   mb::result<game::BlockStateId> get_block(const game::BlockPosition &position) override;
   mb::result<game::LightValue> get_light(game::LightType type, const game::BlockPosition &position) override;
   mb::emptyres set_light(game::LightType type, const game::BlockPosition &position,
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
      m_full = true;
   }

   [[nodiscard]] constexpr bool full() const
   {
      return m_full;
   }

   [[nodiscard]] mb::result<Section &> section(std::int8_t y)
   {
      if (not m_sections.contains(y))
         return mb::error("no such section");

      return m_sections.at(y);
   }

   [[nodiscard]] uuid get_lock() const;
   bool add_ref(uuid engine_id, game::PlayerId player_id);
   void free_ref(game::PlayerId player_id);
   [[nodiscard]] game::ChunkPosition pos() const;

   static mb::result<std::unique_ptr<Chunk>> from_nbt(minecpp::nbt::chunk::v1::Chunk &chunk) noexcept;
   minecpp::nbt::chunk::v1::Chunk to_nbt() noexcept;

 private:
   mb::result<Section &> section_from_y_level(int y);
   [[nodiscard]] HeightContainer &height_by_type(game::HeightType type);
   [[nodiscard]] const HeightContainer &height_by_type(game::HeightType type) const;

   int m_pos_x{}, m_pos_z{};
   bool m_full = false;
   std::array<int, 1024> m_biomes{};
   HeightContainer m_motion_blocking_height;
   HeightContainer m_world_surface_height;
   HeightContainer m_light_blocking_height;
   std::map<int8_t, Section> m_sections;
   std::set<uuid> m_references;
   uuid m_engine_lock{};
};

}// namespace minecpp::world

#endif//MINECPP_GAME_CHUNK_CHUNK_H
