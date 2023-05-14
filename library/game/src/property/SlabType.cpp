#include <cassert>
#include <minecpp/game/property/HalfPlacement.hpp>
#include <minecpp/game/property/SlabType.h>

namespace minecpp::game {

SlabType SlabType::from_half_placement(HalfPlacement half)
{
   switch (half.value()) {
   case HalfPlacement::Top: return Top;
   case HalfPlacement::Bottom: return Bottom;
   }
   assert(false);
   return {};
}

}// namespace minecpp::game