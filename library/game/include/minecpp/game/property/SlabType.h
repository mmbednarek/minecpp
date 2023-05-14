#pragma once

#include <mb/enum.h>

namespace minecpp::game {

class HalfPlacement;

enum class SlabTypeValue
{
   Top,
   Bottom,
   Double
};

using SlabType_Base = mb::enum_wrapper<SlabTypeValue, "top", "bottom", "double">;

class SlabType : public SlabType_Base
{
 public:
   MB_ENUM_TRAITS(SlabType)

   MB_ENUM_FIELD(Top)
   MB_ENUM_FIELD(Bottom)
   MB_ENUM_FIELD(Double)

   static SlabType from_half_placement(HalfPlacement half);
};

}// namespace minecpp::game
