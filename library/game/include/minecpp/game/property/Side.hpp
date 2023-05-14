#pragma once

#include <mb/enum.h>

namespace minecpp::game {

enum class SideValue
{
   Left,
   Right
};

using Side_Base = mb::enum_wrapper<SideValue, "left", "right">;

class Side final : public Side_Base
{
 public:
   MB_ENUM_TRAITS(Side);

   MB_ENUM_FIELD(Left)
   MB_ENUM_FIELD(Right)
};

}// namespace minecpp::game
