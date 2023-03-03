#pragma once
#include "IRandom.h"
#include <minecpp/math/Vector3.h>

namespace minecpp::random {

class Perlin3d
{
   IRandom &rand;
   uint64_t coef1, coef2, coef3, coef4;

 public:
   explicit Perlin3d(IRandom &rand);

   [[nodiscard]] double dot_grad(int x, int y, int z, minecpp::math::Vector3 pos);
   [[nodiscard]] double at(minecpp::math::Vector3 pos);
   [[nodiscard]] minecpp::math::Vector3 grad(int x, int y, int z);
};

}// namespace minecpp::random