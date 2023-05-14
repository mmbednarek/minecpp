#pragma once

#include <mb/enum.h>

namespace minecpp::game {

enum class HalfValue
{
   Lower,
   Upper
};

using Half_Base = mb::enum_wrapper<HalfValue, "lower", "upper">;

class Half final : public Half_Base
{
 public:
   MB_ENUM_TRAITS(Half);

   MB_ENUM_FIELD(Lower)
   MB_ENUM_FIELD(Upper)
};

}
