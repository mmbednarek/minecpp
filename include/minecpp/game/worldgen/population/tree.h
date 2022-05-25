#ifndef MINECPP_TREE_H
#define MINECPP_TREE_H

#pragma once

#include "object.h"
#include <minecpp/random/java_random.h>
#include <unordered_map>

namespace minecpp::game::worldgen::population {

class RandomTree final : public PopObject
{
   random::JavaRandom m_java_random;
   int x1, x2, x3;
   int y1, y2, y3;
   int z1, z2, z3;
   int r1, r2, r3;

   int x_min, x_max;
   int y_min, y_max;
   int z_min, z_max;

   int m_width, m_length, m_height;

 public:
   explicit RandomTree(unsigned seed) :
       m_java_random(seed),
       x1(m_java_random.next_int(6) - 3),
       x2(m_java_random.next_int(6) - 3),
       x3(m_java_random.next_int(6) - 3),
       y1(m_java_random.next_int(6) - 1),
       y2(m_java_random.next_int(6) - 1),
       y3(m_java_random.next_int(6) - 1),
       z1(m_java_random.next_int(6) - 3),
       z2(m_java_random.next_int(6) - 3),
       z3(m_java_random.next_int(6) - 3),
       r1(m_java_random.next_int(3) + 3),
       r2(m_java_random.next_int(3) + 3),
       r3(m_java_random.next_int(3) + 3),
       x_min(std::min(x1 - r1, std::min(x2 - r2, x3 - r3))),
       x_max(std::max(x1 + r1, std::max(x2 + r2, x3 + r3))),
       y_min(std::min(y1 - r1, std::min(y2 - r2, y3 - r3))),
       y_max(std::max(y1 + r1, std::max(y2 + r2, y3 + r3))),
       z_min(std::min(z1 - r1, std::min(z2 - r2, z3 - r3))),
       z_max(std::max(z1 + r1, std::max(z2 + r2, z3 + r3))),
       m_width(x_max - x_min),
       m_length(z_max - z_min),
       m_height(y_max - y_min)
   {
   }

   [[nodiscard]] int width() const override
   {
      return m_width;
   }

   [[nodiscard]] int height() const override
   {
      return m_height + 2;
   }

   [[nodiscard]] int length() const override
   {
      return m_length;
   }

   [[nodiscard]] Pos center() const override
   {
      return {m_width / 2, m_length / 2};
   }

   [[nodiscard]] int block_at(int x, int y, int z) const override;
};

class RandomTreeFactory : public ObjectFactory
{
   std::unordered_map<unsigned, RandomTree> m_trees;

 public:
   PopObject &create(unsigned int seed) override;
   int occurrence() const override;
};

}// namespace minecpp::game::worldgen::population

#endif//MINECPP_TREE_H
