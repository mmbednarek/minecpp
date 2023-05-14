#pragma once

#include <mb/enum.h>
#include <minecpp/math/Vector2.h>

namespace minecpp::game {

class Side;
class Face;

enum class DirectionValues
{
   North,
   South,
   West,
   East
};

using Direction_Base = mb::enum_wrapper<DirectionValues, "north", "south", "west", "east">;

class Direction final : public Direction_Base
{
 public:
   MB_ENUM_TRAITS(Direction);

   MB_ENUM_FIELD(North)
   MB_ENUM_FIELD(South)
   MB_ENUM_FIELD(West)
   MB_ENUM_FIELD(East)

   [[nodiscard]] Direction turn(Side side) const;
   [[nodiscard]] Direction opposite();

   [[nodiscard]] Face to_face();

   [[nodiscard]] static Direction from_vector2(const math::Vector2 &vec);
};

}// namespace minecpp::game