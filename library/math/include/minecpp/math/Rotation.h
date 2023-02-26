#pragma once

namespace minecpp::math {

using Radians = float;
using Degrees = float;

constexpr float g_pi = 3.14159265f;

[[nodiscard]] constexpr Radians degrees_to_radians(Degrees degrees)
{
   return degrees * g_pi / 180.0f;
}

[[nodiscard]] constexpr Degrees radians_to_degrees(Radians radians)
{
   return radians * 180.0f / g_pi;
}

}// namespace minecpp::math