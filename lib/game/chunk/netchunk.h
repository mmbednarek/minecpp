#pragma once
#include "section.h"
#include <minepb/chunk.pb.h>
#include <nbt/reader.h>
#include <string_view>

namespace Game {

struct NetSection {
   uint8_t bits;
   int ref_count;
   std::vector<int> palette;
   std::vector<long long> data;
   std::vector<uint8_t> block_light;
   std::vector<uint8_t> sky_light;
};

struct NetChunk {
   int pos_x, pos_z;
   bool full = false;
   std::array<int, 1024> biomes;
   std::array<uint64_t, 37> hm_motion_blocking;
   std::array<uint64_t, 37> hm_world_surface;
   std::map<int8_t, NetSection> sections;

   explicit NetChunk(NBT::Reader &r);

   void load(NBT::Reader &r, NBT::TagID tagid, const std::string &name);
   void as_proto(minecpp::chunk::NetChunk *chunk);
   void create_empty_section(int8_t sec);
   void set_block(int x, int y, int z, uint32_t state);
   uint8_t get_block_light(int x, int y, int z);
   void set_block_light(int x, int y, int z, uint8_t value);
   void set_sky_light(int x, int y, int z, uint8_t value);
};

} // namespace Game
