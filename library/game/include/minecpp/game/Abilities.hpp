#pragma once

#include <cstdint>

namespace minecpp::game {

struct Abilities
{
   float fly_speed    = 0.05f;
   bool flying        = false;
   bool instant_build = true;
   bool invulnerable  = false;
   bool may_build     = false;
   bool may_fly       = false;
   float field_of_view = 0.1f;

   [[nodiscard]] constexpr std::uint32_t flags() const
   {
      return (invulnerable ? 1u : 0u) | (flying ? 2u : 0u) | (may_fly ? 4u : 0u) | (instant_build ? 8u : 0u);
   }
};

}// namespace minecpp::game