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

} // namespace Game
