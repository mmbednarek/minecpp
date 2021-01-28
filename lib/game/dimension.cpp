#include <minecpp/game/dimension.h>

namespace Game {

minecpp::game::DimensionType dimension_to_proto(Dimension d) {
   switch (d) {
   case Dimension::Overworld:
      return minecpp::game::DimensionType::Overworld;
   case Dimension::Nether:
      return minecpp::game::DimensionType::Nether;
   case Dimension::End:
      return minecpp::game::DimensionType::End;
   }
   return minecpp::game::DimensionType::Overworld;
}

void DimensionProperties::to_nbt(NBT::Writer &w) const {
   w.write_byte("piglin_safe", piglin_safe);
   w.write_byte("natural", natural);
   w.write_float("ambient_light", ambient_light);
   w.write_string("infiniburn", infiniburn);
   w.write_byte("respawn_anchor_works", respawn_anchor_works);
   w.write_byte("has_skylight", has_skylight);
   w.write_byte("bed_works", bed_works);
   w.write_string("effetcs", "minecraft:overworld");
   w.write_byte("has_raids", has_raids);
   w.write_int("logical_height", logical_height);
   w.write_float("coordinate_scale", 1.0);
   w.write_byte("ultrawarm", ultrawarm);
   w.write_byte("has_ceiling", has_ceiling);
}

void write_dimension_codec(NBT::Writer &w) {
   w.begin_compound("");
   w.begin_compound("minecraft:dimension_type");
   w.write_string("type", "minecraft:dimension_type");
   w.begin_list("value", NBT::TagId::Compound, 1);
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
   w.begin_list("value", NBT::TagId::Compound, 2);
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
   w.end_compound();
}

void write_dimension_type(NBT::Writer &w) {
   w.begin_compound("");
   OverworldProps.to_nbt(w);
   w.end_compound();
}

}// namespace Game
