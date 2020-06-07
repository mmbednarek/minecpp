#pragma once
#include "section.h"
#include <nbt/reader.h>
#include <string_view>
#include <minepb/chunk.pb.h>

namespace Game {

struct NetSection {
   uint8_t bits;
   int ref_count;
   std::vector<int> palette;
   std::vector<long long> data;
};

struct NetChunk {
   int pos_x, pos_z;
   bool full = false;
   std::array<int, 1024> biomes;
   std::array<uint64_t, 36> hm_motion_blocking;
   std::array<uint64_t, 36> hm_world_surface;
   std::map<uint8_t, NetSection> sections;

   explicit NetChunk(NBT::Reader &r);

   void load(NBT::Reader &r, NBT::TagID tagid, const std::string &name);
   void as_proto(minecpp::chunk::NetChunk *chunk);
};

} // namespace Game
