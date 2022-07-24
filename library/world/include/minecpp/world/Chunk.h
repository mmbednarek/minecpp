#ifndef MINECPP_GAME_CHUNK_CHUNK_H
#define MINECPP_GAME_CHUNK_CHUNK_H

#include "Section.h"
#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <minecpp/game/Game.h>
#include <minecpp/nbt/chunk/v1/Chunk.nbt.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Tag.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <string_view>

namespace minecpp::world {

using boost::uuids::uuid;

struct Chunk
{
   int m_pos_x, m_pos_z;
   bool m_full = false;
   std::array<int, 1024> m_biomes;
   std::array<uint64_t, 37> m_hm_motion_blocking;
   std::array<uint64_t, 37> m_hm_world_surface;
   std::map<int8_t, Section> m_sections;
   std::set<uuid> m_references;
   uuid m_engine_lock{};

   Chunk();
   Chunk(int x, int z, std::array<short, 256> &height_map);

   void as_proto(minecpp::proto::chunk::v1::Chunk *chunk);
   void create_empty_section(int8_t sec);
   void set_block(int x, int y, int z, game::BlockStateId state);
   game::BlockStateId get_block(int x, int y, int z);
   mb::result<game::LightLevel> get_block_light(game::BlockPosition position);
   mb::result<game::LightLevel> get_sky_light(game::BlockPosition position);
   mb::emptyres set_block_light(game::BlockPosition position, game::LightLevel value);
   mb::emptyres set_sky_light(game::BlockPosition position, game::LightLevel value);
   int height_at(int x, int z);
   void put_section(int8_t level, Section sec);
   std::array<short, 256> get_height_map();

   [[nodiscard]] uuid get_lock() const;
   bool add_ref(uuid engine_id, game::PlayerId player_id);
   void free_ref(game::PlayerId player_id);
   [[nodiscard]] game::ChunkPosition pos() const;

   static mb::result<std::unique_ptr<Chunk>> from_nbt(minecpp::nbt::chunk::v1::Chunk &chunk) noexcept;
   minecpp::nbt::chunk::v1::Chunk to_nbt() noexcept;

 private:
   mb::result<Section &> section_from_y_level(int y);
};

}// namespace minecpp::world

#endif//MINECPP_GAME_CHUNK_CHUNK_H
