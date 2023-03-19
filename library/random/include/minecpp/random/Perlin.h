#pragma once
#include "IRandom.h"
#include <minecpp/math/Vector2.h>

namespace minecpp::random {

class Perlin
{
 public:
   explicit Perlin(IRandom &rand);

   [[nodiscard]] double dot_grad(int x, int z, math::Vector2 pos);
   [[nodiscard]] double at(math::Vector2 pos);
   [[nodiscard]] math::Vector2 grad(int x, int z) const;

 private:
   int m_coefficient1;
   int m_coefficient2;
   int m_coefficient3;
};

class DisplacedPerlin
{
 public:
   explicit DisplacedPerlin(IRandom &rand, double scale, double amp);

   [[nodiscard]] double at(minecpp::math::Vector2 pos);

 private:
   Perlin m_base_perlin;
   Perlin m_x_displacement;
   Perlin m_z_displacement;

   double m_scale;
   double m_amp;
   math::Vector2 m_move_dis_x;
   math::Vector2 m_move_dis_z;
};

}// namespace minecpp::random
