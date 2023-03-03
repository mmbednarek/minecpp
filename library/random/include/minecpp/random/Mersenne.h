#pragma once
#include "IRandom.h"
#include <random>

namespace minecpp::random {

class Mersenne : public IRandom
{
   std::mt19937_64 engine;

 public:
   explicit Mersenne(uint64_t seed);

   int next_int() override;
   int next_int(uint32_t bound) override;
   double next_double() override;
   void reset_seed(uint64_t seed) override;
};

}// namespace minecpp::random
