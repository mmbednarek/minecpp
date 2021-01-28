#include <minecpp/minerandom/java_random.h>
#include <minecpp/minerandom/random.h>

namespace Rand {

constexpr auto MULTIPLIER = 0x5DEECE66DULL;
constexpr auto ADDEND = 0xBULL;
constexpr auto MASK = (1ULL << 48ULL) - 1;
constexpr auto DOUBLE_UNIT = 0x1.0p-53;

JavaRandom::JavaRandom(uint64_t seed) { _seed = (seed ^ MULTIPLIER) & MASK; }

int JavaRandom::next(int bits) {
   _seed = (_seed * MULTIPLIER + ADDEND) & MASK;
   return (int)(_seed >> (48ULL - bits));
}

int JavaRandom::next_int() { return next(32); }

int JavaRandom::next_int(const uint32_t bound) {
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

double JavaRandom::next_double() {
   return static_cast<double>((static_cast<uint64_t>(next(26)) << 27u) + next(27)) * DOUBLE_UNIT;
}

void JavaRandom::reset_seed(uint64_t seed) {
   _seed = (seed ^ MULTIPLIER) & MASK;
}


} // namespace Utils
