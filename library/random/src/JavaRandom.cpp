#include "minecpp/random/IRandom.h"
#include <minecpp/random/JavaRandom.h>

namespace minecpp::random {

constexpr auto g_multiplier  = 0x5DEECE66DULL;
constexpr auto g_addend      = 0xBULL;
constexpr auto g_mask        = (1ULL << 48ULL) - 1;
constexpr auto g_double_unit = 0x1.0p-53;

JavaRandom::JavaRandom(std::uint64_t seed)
{
   m_seed = (seed ^ g_multiplier) & g_mask;
}

int JavaRandom::next(int bits)
{
   m_seed = (m_seed * g_multiplier + g_addend) & g_mask;
   return (int) (m_seed >> (48ULL - static_cast<std::uint64_t>(bits)));
}

int JavaRandom::next_int()
{
   return next(32);
}

int JavaRandom::next_int(const std::uint32_t bound)
{
   auto r          = static_cast<std::uint32_t>(next(31));
   std::uint32_t m = bound - 1;
   if ((bound & m) == 0)
      r = (bound * r) >> 31ULL;
   else {
      for (auto u{r}; static_cast<int>(u - (r = u % bound) + m) < 0; u = static_cast<std::uint32_t>(next(31)))
         ;
   }
   return static_cast<int>(r);
}

double JavaRandom::next_double()
{
   return static_cast<double>((static_cast<std::uint64_t>(next(26)) << 27u) +
                              static_cast<std::uint64_t>(next(27))) *
          g_double_unit;
}

void JavaRandom::reset_seed(std::uint64_t seed)
{
   m_seed = (seed ^ g_multiplier) & g_mask;
}


}// namespace minecpp::random
