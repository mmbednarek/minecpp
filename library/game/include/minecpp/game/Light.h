#pragma once

#include "BlockPosition.h"

#include <mb/enum.h>
#include <mb/int.h>

namespace minecpp::game {

enum class LightTypeValue
{
   Block,
   Sky
};

using LightType_Base = mb::enum_wrapper<LightTypeValue, "block", "sky">;

class LightType final : public LightType_Base
{
 public:
   MB_ENUM_TRAITS(LightType);

   MB_ENUM_FIELD(Block)
   MB_ENUM_FIELD(Sky)
};

struct LightSource
{
   BlockPosition position{};
   mb::u8 strength{};

   LightSource();

   LightSource(const BlockPosition &position, mb::u8 strength);
};

}// namespace minecpp::game