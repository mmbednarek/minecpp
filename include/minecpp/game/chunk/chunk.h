#pragma once
#include "section.h"
#include <boost/uuid/uuid.hpp>
#include <minecpp/error/result.h>
#include <minecpp/game/block/position.h>
#include <minecpp/nbt/reader.h>
#include <minecpp/nbt/tag.h>
#include <minepb/chunk.pb.h>
#include <string_view>

namespace minecpp::game {

using boost::uuids::uuid;

struct Chunk {
   int pos_x, pos_z;
   bool full = false;
   std::array<int, 1024> biomes;
   std::array<uint64_t, 37> hm_motion_blocking;
   std::array<uint64_t, 37> hm_world_surface;
   std::map<int8_t, Section> sections;
   std::set<uuid> refs;
   uuid engine_lock{};

   Chunk();
   Chunk(int x, int z, std::array<short, 256> &height_map);

   result<empty> load(nbt::Reader &r, nbt::TagId tagid, const std::string &name);
   void as_proto(minecpp::chunk::NetChunk *chunk);
   void create_empty_section(int8_t sec);
   void set_block(int x, int y, int z, uint32_t state);
   uint8_t get_block_light(int x, int y, int z);
   void set_block_light(int x, int y, int z, uint8_t value);
   void set_sky_light(int x, int y, int z, uint8_t value);
   int height_at(int x, int z);
   void put_section(int8_t level, Section sec);
   std::array<short, 256> get_height_map();

   [[nodiscard]] uuid get_lock() const;
   bool add_ref(uuid engine_id, uuid player_id);
   void free_ref(uuid player_id);
   block::ChunkPos pos() const;

   static result<std::unique_ptr<Chunk>> from_nbt(nbt::Reader &r);
};

struct PaletteItem {
   std::string tag_name;
   nbt::CompoundContent properties;

   explicit PaletteItem(nbt::Reader &r);
   uint32_t to_state_id();
};

}// namespace minecpp::game
