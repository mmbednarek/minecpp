#include <cassert>
#include <minecpp/game/property/Direction.h>
#include <minecpp/game/property/Face.h>
#include <minecpp/game/property/Side.hpp>

namespace minecpp::game {

Direction Direction::turn(Side side) const
{
   if (side == Side::Left) {
      switch (value()) {
      case Direction::North: return Direction::West;
      case Direction::South: return Direction::East;
      case Direction::West: return Direction::South;
      case Direction::East: return Direction::North;
      }
   } else {
      switch (value()) {
      case Direction::North: return Direction::East;
      case Direction::South: return Direction::West;
      case Direction::West: return Direction::North;
      case Direction::East: return Direction::South;
      }
   }

   assert(false && "not reachable");
   return {};
}

Face Direction::to_face()
{
   switch (value()) {
   case Direction::North: return Face::North;
   case Direction::South: return Face::South;
   case Direction::West: return Face::West;
   case Direction::East: return Face::East;
   }

   assert(false && "not reachable");
   return {};
}

Direction Direction::from_vector2(const math::Vector2 &vec)
{
   bool x_dominant = std::abs(vec.x()) > std::abs(vec.y());
   if (x_dominant) {
      if (vec.x() > 0.0)
         return Direction::East;
      return Direction::West;
   }

   if (vec.y() > 0.0)
      return Direction::South;
   return Direction::North;
}

Direction Direction::opposite()
{
   switch (value()) {
   case East: return West;
   case West: return East;
   case South: return North;
   case North: return South;
   }

   assert(false);
   return {};
}
}// namespace minecpp::game
