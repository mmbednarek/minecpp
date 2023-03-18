#pragma once
#include <cmath>

namespace minecpp::math {

template<typename TValue>
constexpr TValue crop(TValue value, TValue min, TValue max)
{
   if (value < min)
      return min;
   if (value > max)
      return max;
   return value;
}

template<typename TValue>
constexpr TValue lerp(TValue value, TValue min, TValue max)
{
   return min + value * (max - min);
}

template<typename TFloat>
TFloat fmod(TFloat value, const TFloat mod)
{
   static constexpr TFloat zero{};

   if (value > mod)
      return std::fmod(value, mod);
   if (value < zero)
      return mod + std::fmod(value, mod);

   return value;
}

}// namespace minecpp::math