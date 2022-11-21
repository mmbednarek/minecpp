#pragma once
#include "Random.h"
#include <cstdint>

namespace minecpp::random {

class JavaRandom : public Random
{
 public:
   explicit JavaRandom(uint64_t seed);

   [[nodiscard]] int next_int() override;
   [[nodiscard]] int next_int(uint32_t bound) override;
   [[nodiscard]] double next_double() override;
   void reset_seed(uint64_t seed) override;

 private:
   int next(int bits);

   uint64_t _seed;
};

}// namespace minecpp::random
