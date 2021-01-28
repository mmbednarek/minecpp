#pragma once
#include "random.h"
#include <minecpp/util/vec.h>

namespace Rand {

class Perlin3d {
   Random &rand;
   uint64_t coef1, coef2, coef3, coef4;

 public:
   explicit Perlin3d(Random &rand);

   [[nodiscard]] double dot_grad(int x, int y, int z, Utils::Vec3 pos);
   [[nodiscard]] double at(Utils::Vec3 pos);
   [[nodiscard]] Utils::Vec3 grad(int x, int y, int z);
};

}