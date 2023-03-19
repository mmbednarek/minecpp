#pragma once
#include "IRandom.h"
#include <random>

namespace minecpp::random {

class Mersenne : public IRandom
{
 public:
   explicit Mersenne(std::uint64_t seed);

   int next_int() override;
   int next_int(std::uint32_t bound) override;
   double next_double() override;
   void reset_seed(std::uint64_t seed) override;

 private:
   std::mt19937_64 m_engine;
};

}// namespace minecpp::random
