#pragma once

#include <mb/enum.h>

namespace minecpp::game {

enum class HalfPlacementValue
{
   Top,
   Bottom
};

using HalfPlacement_Base = mb::enum_wrapper<HalfPlacementValue, "top", "bottom">;

class HalfPlacement final : public HalfPlacement_Base
{
 public:
   MB_ENUM_TRAITS(HalfPlacement);

   MB_ENUM_FIELD(Top)
   MB_ENUM_FIELD(Bottom)
};

}
