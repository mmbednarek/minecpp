#pragma once
#include <minecpp/random/random.h>
#include <minecpp/util/vec.h>

namespace Rand {

class Perlin {
   Random &rand;
   uint64_t coef1, coef2, coef3;

 public:
   explicit Perlin(Random &rand);

   [[nodiscard]] double dot_grad(int x, int z, Utils::Vec2 pos);
   [[nodiscard]] double at(Utils::Vec2 pos);
   [[nodiscard]] Utils::Vec2 grad(int x, int z);
};

class DisplacedPerlin {
   Perlin base;
   Perlin dis_x;
   Perlin dis_z;

   double scale;
   double amp;
   Utils::Vec2 move_dis_x;
   Utils::Vec2 move_dis_z;

 public:
   explicit DisplacedPerlin(Random &rand, double scale, double amp);

   [[nodiscard]] double at(Utils::Vec2 pos);
};

}// namespace Rand
