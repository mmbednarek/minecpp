#include <minecpp/game/Game.h>
#include <minecpp/game/property/Face.h>

namespace minecpp::game {

namespace pb_common = minecpp::proto::common::v1;

Face Face::from_proto(const pb_common::Face face)
{
   return Face{static_cast<FaceValue>(face)};
}

pb_common::Face Face::to_proto()
{
   return static_cast<pb_common::Face>(index());
}

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
