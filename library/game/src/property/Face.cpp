#include <minecpp/game/Game.h>
#include <minecpp/game/property/Face.h>

namespace minecpp::game {

Face Face::opposite_face()
{
   switch (value()) {
   case Face::Bottom: return Face::Top;
   case Face::Top: return Face::Bottom;
   case Face::North: return Face::South;
   case Face::South: return Face::North;
   case Face::West: return Face::East;
   case Face::East: return Face::West;
   }

   assert(false && "SHOULD NOT BE REACHED");
   return {};
}

FaceMask Face::to_mask()
{
   switch (value()) {
   case Face::Bottom: return FaceMask::Bottom;
   case Face::Top: return FaceMask::Top;
   case Face::North: return FaceMask::North;
   case Face::South: return FaceMask::South;
   case Face::West: return FaceMask::West;
   case Face::East: return FaceMask::East;
   }

   assert(false && "SHOULD NOT BE REACHED");
   return {};
}

bool operator&(FaceMask lhs, Face rhs)
{
   return lhs & rhs.to_mask();
}

}// namespace minecpp::game
