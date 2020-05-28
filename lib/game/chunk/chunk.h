#pragma once
#include "section.h"
#include <nbt/reader.h>
#include <string_view>

namespace Game {

struct Chunk {
   typedef std::array<uint16_t, 256> HeightMap;

   std::string status;
   int pos_x, pos_z;
   bool light_on;

   std::vector<int> biomes;

   HeightMap hm_motion_blocking;
   HeightMap hm_motion_blocking_no_leaves;
   HeightMap hm_motion_ocean_floor;
   HeightMap hm_world_surface;

   int64_t inhabited_time;
   int64_t last_update;

   std::array<uint8_t, 2048> sky_light;
   std::map<uint8_t, Section> sections;

   explicit Chunk(NBT::Reader &r);

   void load(NBT::Reader &r, NBT::TagID tagid, const std::string &name);
   HeightMap read_height_map(NBT::Reader &r, NBT::TagID type);
   std::string_view block_at(int x, int y, int z);
};

} // namespace Game
