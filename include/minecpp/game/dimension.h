#pragma once
#include <cstdint>
#include <minecpp/nbt/writer.h>
#include <minepb/game.pb.h>

namespace minecpp::game {

class DimensionProperties {
 public:
   bool piglin_safe = false;
   bool natural = true;
   float ambient_light = 0.0f;
   std::string infiniburn = "minecraft:infiniburn_overworld";
   bool respawn_anchor_works = false;
   bool has_skylight = true;
   bool bed_works = true;
   bool has_raids = true;
   std::string name = "minecraft:overworld";
   int logical_height = 256;
   bool shrunk = false;
   bool ultrawarm = false;
   bool has_ceiling = false;

   void to_nbt(nbt::Writer &w) const;
};

const DimensionProperties OverworldProps{};
const DimensionProperties OverworldCavesProps{
    .name = "minecraft:overworld",
    .has_ceiling = true,
};
const DimensionProperties NetherProps{
    .piglin_safe = true,
    .natural = false,
    .ambient_light = 0.1f,
    .infiniburn = "minecraft:infiniburn_nether",
    .respawn_anchor_works = true,
    .has_skylight = false,
    .bed_works = false,
    .name = "minecraft:the_nether",
    .logical_height = 128,
    .shrunk = true,
    .ultrawarm = true,
    .has_ceiling = true,
};
const DimensionProperties EndProps{
    .natural = false,
    .infiniburn = "minecraft:infiniburn_end",
    .respawn_anchor_works = false,
    .has_skylight = false,
    .bed_works = false,
    .has_raids = true,
    .name = "minecraft:the_end",
};

void write_dimension_codec(nbt::Writer &w);
void write_dimension_type(nbt::Writer &w);

enum class Dimension : int8_t { Overworld = 0, Nether = -1, End = 1 };

minecpp::game::DimensionType dimension_to_proto(Dimension d);

constexpr uint32_t world_limit = 30000000;

} // namespace minecpp::game