#pragma once
#include <nbt/reader.h>

namespace Game {

struct Chunk {
   struct PaletteItem {
      explicit PaletteItem(NBT::Reader &r);
      std::string tag_name;
   };
   struct Section {
      std::array<uint8_t, 2048> light;
      std::array<uint8_t, 2048> sky_light;
      std::array<uint8_t, 4096> block;
      std::vector<PaletteItem> palette;
   };
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
   std::array<std::shared_ptr<Section>, 16> sections;

   explicit Chunk(NBT::Reader &r);

   void load(NBT::Reader &r, NBT::TagID tagid, const std::string &name);
   HeightMap read_height_map(NBT::Reader &r, NBT::TagID type);
   void read_section(NBT::Reader &r);
};

} // namespace Game
