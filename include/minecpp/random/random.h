#pragma once
#include <cstdint>

namespace minecpp::random {

class Random
{
 public:
   [[nodiscard]] virtual int next_int()               = 0;
   [[nodiscard]] virtual int next_int(uint32_t bound) = 0;
   [[nodiscard]] virtual double next_double()         = 0;
   virtual void reset_seed(uint64_t seed)             = 0;
};

}// namespace minecpp::random