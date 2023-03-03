#pragma once
#include "IRandom.h"
#include <minecpp/math/Vector2.h>

namespace minecpp::random {

class Perlin
{
   IRandom &rand;
   uint64_t coef1, coef2, coef3;

 public:
   explicit Perlin(IRandom &rand);

   [[nodiscard]] double dot_grad(int x, int z, minecpp::math::Vector2 pos);
   [[nodiscard]] double at(minecpp::math::Vector2 pos);
   [[nodiscard]] minecpp::math::Vector2 grad(int x, int z);
};

class DisplacedPerlin
{
   Perlin base;
   Perlin dis_x;
   Perlin dis_z;

   double scale;
   double amp;
   minecpp::math::Vector2 move_dis_x;
   minecpp::math::Vector2 move_dis_z;

 public:
   explicit DisplacedPerlin(IRandom &rand, double scale, double amp);

   [[nodiscard]] double at(minecpp::math::Vector2 pos);
};

}// namespace minecpp::random
