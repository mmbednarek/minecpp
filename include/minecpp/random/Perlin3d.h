#pragma once
#include "Random.h"
#include <minecpp/util/Vec.h>

namespace minecpp::random {

class Perlin3d
{
   Random &rand;
   uint64_t coef1, coef2, coef3, coef4;

 public:
   explicit Perlin3d(Random &rand);

   [[nodiscard]] double dot_grad(int x, int y, int z, minecpp::util::Vec3 pos);
   [[nodiscard]] double at(minecpp::util::Vec3 pos);
   [[nodiscard]] minecpp::util::Vec3 grad(int x, int y, int z);
};

}// namespace minecpp::random