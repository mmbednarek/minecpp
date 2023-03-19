#pragma once
#include "IRandom.h"
#include <minecpp/math/Vector3.h>

namespace minecpp::random {

class Perlin3D
{
 public:
   explicit Perlin3D(IRandom &rand);

   [[nodiscard]] double dot_grad(int x, int y, int z, const math::Vector3 &pos) const;
   [[nodiscard]] double at(const math::Vector3 &pos) const;
   [[nodiscard]] math::Vector3 grad(int x, int y, int z) const;

 private:
   int m_coefficient1;
   int m_coefficient2;
   int m_coefficient3;
   int m_coefficient4;
};

}// namespace minecpp::random