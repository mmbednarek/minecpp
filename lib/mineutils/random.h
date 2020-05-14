#pragma once
#include <cstdint>

namespace Utils {

class Random {
 public:
   explicit Random(uint64_t seed);

   int next_int();
   int next_int(uint32_t bound);

 private:
   int next(int bits);

   uint64_t _seed;
};

} // namespace Utils
