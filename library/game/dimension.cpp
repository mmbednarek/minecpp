#include <minecpp/game/dimension.h>

namespace minecpp::game {

proto::common::v1::DimensionType dimension_to_proto(Dimension d)
{
   using proto::common::v1::DimensionType;

   switch (d) {
   case Dimension::Overworld: return DimensionType::Overworld;
   case Dimension::Nether: return DimensionType::Nether;
   case Dimension::End: return DimensionType::End;
   }
   return DimensionType::Overworld;
}

void DimensionProperties::to_nbt(nbt::Writer &w) const
{
   w.write_byte("piglin_safe", piglin_safe);
   w.write_byte("natural", natural);
   w.write_float("ambient_light", ambient_light);
   w.write_string("infiniburn", infiniburn);
   w.write_byte("respawn_anchor_works", respawn_anchor_works);
   w.write_byte("has_skylight", has_skylight);
   w.write_byte("bed_works", bed_works);
   w.write_string("effetcs", "minecraft:overworld");
   w.write_byte("has_raids", has_raids);
   w.write_int("min_y", 0);
   w.write_int("height", logical_height);
   w.write_int("logical_height", logical_height);
   w.write_double("coordinate_scale", 1.0);
   w.write_byte("ultrawarm", ultrawarm);
   w.write_byte("has_ceiling", has_ceiling);
   w.write_int("monster_spawn_block_light_limit", 10);
   w.write_int("monster_spawn_light_level", 5);
}

void write_dimension_codec(nbt::Writer &w)
{
   w.begin_compound("");
   w.begin_compound("minecraft:dimension_type");
   w.write_string("type", "minecraft:dimension_type");
   w.begin_list("value", nbt::TagId::Compound, 1);
   {
      w.write_string("name", "minecraft:overworld");
      w.write_int("id", 0);
      w.begin_compound("element");
      OverworldProps.to_nbt(w);
      w.end_compound();
      w.end_compound();
   }
   w.end_compound();
   w.begin_compound("minecraft:worldgen/biome");
   w.write_string("type", "minecraft:worldgen/biome");
   w.begin_list("value", nbt::TagId::Compound, 2);
   {
      w.write_string("name", "minecraft:plains");
      w.write_int("id", 0);
      w.begin_compound("element");
      {
         w.write_string("precipitation", "none");
         w.write_float("depth", 1.5);
         w.write_float("temperature", 1.5);
         w.write_float("scale", 1.0);
         w.write_float("downfall", 1.0);
         w.write_string("category", "plains");
         w.begin_compound("effects");
         w.write_int("sky_color", 12833240);
         w.write_int("water_fog_color", 16054521);
         w.write_int("fog_color", 16054521);
         w.write_int("water_color", 6326951);
         w.end_compound();
      }
      w.end_compound();
      w.end_compound();
      w.write_string("name", "minecraft:mountains");
      w.write_int("id", 1);
      w.begin_compound("element");
      {
         w.write_string("precipitation", "none");
         w.write_float("depth", 1.0);
         w.write_float("temperature", -0.5);
         w.write_float("scale", 1.0);
         w.write_float("downfall", 1.0);
         w.write_string("category", "icy");
         w.begin_compound("effects");
         w.write_int("sky_color", 12833240);
         w.write_int("water_fog_color", 16054521);
         w.write_int("fog_color", 16054521);
         w.write_int("water_color", 6326951);
         w.end_compound();
      }
      w.end_compound();
      w.end_compound();
   }
   w.end_compound();
   w.begin_compound("minecraft:chat_type");
   w.write_string("type", "minecraft:chat_type");
   w.begin_list("value", nbt::TagId::Compound, 1);
   {
      w.write_string("name", "minecraft:system");
      w.write_int("id", 0);

      w.begin_compound("element");

      w.begin_compound("narration");
      w.write_string("priority", "system");
      w.end_compound();

      w.end_compound();

      w.end_compound();
   }
   w.end_compound();
   w.end_compound();
}

void write_dimension_type(nbt::Writer &w)
{
   w.begin_compound("");
   OverworldProps.to_nbt(w);
   w.end_compound();
}

nbt::repository::v1::DimensionTypeDescription get_overworld_description()
{
   nbt::repository::v1::DimensionTypeDescription out{};
   out.piglin_safe                     = false;
   out.natural                         = true;
   out.ambient_light                   = 0.0f;
   out.infiniburn                      = "#minecraft:infiniburn_overworld";
   out.respawn_anchor_works            = false;
   out.has_skylight                    = true;
   out.bed_works                       = true;
   out.has_raids                       = true;
   out.min_y                           = 0;
   out.logical_height                  = 256;
   out.coordinate_scale                = 1.0;
   out.ultrawarm                       = false;
   out.has_ceiling                     = false;
   out.monster_spawn_block_light_limit = 10;
   out.monster_spawn_light_level       = 5;
   return out;
}

nbt::repository::v1::BiomeDescription get_biome_plains_description()
{
   nbt::repository::v1::BiomeDescription biomes{};
   biomes.precipitation           = "none";
   biomes.depth                   = 1.5;
   biomes.temperature             = 1.5;
   biomes.scale                   = 1.0;
   biomes.downfall                = 1.0;
   biomes.category                = "plains";
   biomes.effects.sky_color       = 12833240;
   biomes.effects.water_fog_color = 16054521;
   biomes.effects.fog_color       = 16054521;
   biomes.effects.water_color     = 6326951;
   return biomes;
}

nbt::repository::v1::BiomeDescription get_biome_moutains_description()
{
   nbt::repository::v1::BiomeDescription biomes{};
   biomes.precipitation           = "none";
   biomes.depth                   = 1.0;
   biomes.temperature             = -0.5;
   biomes.scale                   = 1.0;
   biomes.downfall                = 1.0;
   biomes.category                = "icy";
   biomes.effects.sky_color       = 12833240;
   biomes.effects.water_fog_color = 16054521;
   biomes.effects.fog_color       = 16054521;
   biomes.effects.water_color     = 6326951;
   return biomes;
}

nbt::repository::v1::ChatTypeDescription get_system_chat_description()
{
   nbt::repository::v1::ChatTypeDescription chat{};
   chat.narration.priority = "system";
   return chat;
}

nbt::repository::v1::Registry get_registry()
{
   nbt::repository::v1::Registry registry;
   registry.dimension_types.type = "minecraft:dimension_type";

   nbt::repository::v1::DimensionTypeEntry overworld{};
   overworld.name    = "minecraft:overworld";
   overworld.id      = 0;
   overworld.element = get_overworld_description();
   registry.dimension_types.value.push_back(overworld);

   registry.biomes.type = "minecraft:worldgen/biome";

   nbt::repository::v1::BiomeEntry plains;
   plains.name    = "minecraft:plains";
   plains.id      = 0;
   plains.element = get_biome_plains_description();
   registry.biomes.value.push_back(plains);

   nbt::repository::v1::BiomeEntry mountains;
   plains.name    = "minecraft:mountains";
   plains.id      = 1;
   plains.element = get_biome_moutains_description();
   registry.biomes.value.push_back(mountains);

   registry.chat_types.type = "minecraft:chat_type";

   nbt::repository::v1::ChatTypeEntry system;
   system.name    = "minecraft:mountains";
   system.id      = 1;
   system.element = get_system_chat_description();
   registry.chat_types.value.push_back(system);

   return registry;
}

}// namespace minecpp::game
