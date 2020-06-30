#include "dimension.h"

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
   w.write_byte("has_raids", has_raids);
   w.write_string("name", name);
   w.write_int("logical_height", logical_height);
   w.write_byte("shrunk", shrunk);
   w.write_byte("ultrawarm", ultrawarm);
   w.write_byte("has_ceiling", has_ceiling);
}

void write_dimensions(NBT::Writer &w) {
   w.begin_compound("");
   w.begin_list("dimension", NBT::Compound, 4);
   {
      OverworldProps.to_nbt(w);
      w.end_compound();
      OverworldProps.to_nbt(w);
      w.end_compound();
      OverworldProps.to_nbt(w);
      w.end_compound();
      OverworldProps.to_nbt(w);
      w.end_compound();
   }
   w.end_compound();
}

} // namespace Game
