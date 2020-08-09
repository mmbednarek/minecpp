#pragma once
#include <boost/uuid/uuid.hpp>
#include <error/result.h>
#include <minepb/chunk.pb.h>
#include <nbt/reader.h>
#include <nbt/tag.h>
#include <string_view>

namespace Game {

struct Section {
   uint8_t bits;
   int ref_count;
   std::vector<int> palette;
   std::vector<int64_t> data;
   std::vector<uint8_t> block_light;
   std::vector<uint8_t> sky_light;
};

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

   result<empty> load(NBT::Reader &r, NBT::TagId tagid, const std::string &name);
   void as_proto(minecpp::chunk::NetChunk *chunk);
   void create_empty_section(int8_t sec);
   void set_block(int x, int y, int z, uint32_t state);
   uint8_t get_block_light(int x, int y, int z);
   void set_block_light(int x, int y, int z, uint8_t value);
   void set_sky_light(int x, int y, int z, uint8_t value);
   int height_at(int x, int z);

   [[nodiscard]] uuid get_lock() const;
   bool add_ref(uuid engine_id, uuid player_id);
   void free_ref(uuid player_id);

   static result<std::unique_ptr<Chunk>> from_nbt(NBT::Reader &r);
};

struct PaletteItem {
   std::string tag_name;
   NBT::CompoundContent properties;

   explicit PaletteItem(NBT::Reader &r);
   uint32_t to_state_id();
};

}// namespace Game
