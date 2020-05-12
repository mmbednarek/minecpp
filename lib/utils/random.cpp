#include "random.h"
#include <stdexcept>

namespace Utils {

#define MULTIPLIER 0x5DEECE66DULL
#define ADDEND 0xBULL
#define MASK (1ULL << 48ULL) - 1

Random::Random(uint64_t seed) { _seed = (seed ^ MULTIPLIER) & MASK; }

int Random::next(int bits) {
   _seed = (_seed * MULTIPLIER + ADDEND) & MASK;
   return (int)(_seed >> (48ULL - bits));
}

int Random::next_int() { return next(32); }

int Random::next_int(uint32_t bound) {
   int r = next(31);
   uint32_t m = bound - 1;
   if ((bound & m) == 0)
      r = (int)((bound * (uint64_t)r) >> 31ULL);
   else {
      for (uint64_t u = r; u - (r = u % bound) + m < 0; u = next(31))
         ;
   }
   return r;
}

} // namespace Utils
