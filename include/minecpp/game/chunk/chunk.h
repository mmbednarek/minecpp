#ifndef MINECPP_GAME_CHUNK_CHUNK_H
#define MINECPP_GAME_CHUNK_CHUNK_H

#include "minecpp/game/game.h"
#include "section.h"
#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <minecpp/game/block/position.h>
#include <minecpp/nbt/chunk/v1/chunk.nbt.h>
#include <minecpp/nbt/reader.h>
#include <minecpp/nbt/tag.h>
#include <minecpp/player/id.h>
#include <minecpp/proto/chunk/v1/chunk.pb.h>
#include <string_view>

namespace minecpp::game {

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
   void set_block(int x, int y, int z, uint32_t state);
   game::BlockState get_block(int x, int y, int z);
   uint8_t get_block_light(int x, int y, int z);
   void set_block_light(int x, int y, int z, uint8_t value);
   void set_sky_light(int x, int y, int z, uint8_t value);
   int height_at(int x, int z);
   void put_section(int8_t level, Section sec);
   std::array<short, 256> get_height_map();

   [[nodiscard]] uuid get_lock() const;
   bool add_ref(uuid engine_id, player::Id player_id);
   void free_ref(player::Id player_id);
   [[nodiscard]] block::ChunkPos pos() const;

   static mb::result<std::unique_ptr<Chunk>> from_nbt(minecpp::nbt::chunk::v1::Chunk &chunk) noexcept;
   minecpp::nbt::chunk::v1::Chunk to_nbt() noexcept;
};

}// namespace minecpp::game

#endif//MINECPP_GAME_CHUNK_CHUNK_H
