#ifndef MINECPP_TREE_H
#define MINECPP_TREE_H

#pragma once

#include "Object.h"
#include <minecpp/random/JavaRandom.h>
#include <unordered_map>

namespace minecpp::world::population {

struct LeaveBlob
{
   int x{}, y{}, z{}, r{};

   LeaveBlob() = default;

   explicit LeaveBlob(random::JavaRandom &random, int range, int min_size, int max_size) :
       x(random.next_int(static_cast<uint32_t>(2 * range)) - range),
       y(random.next_int(static_cast<uint32_t>(2 * range)) - range),
       z(random.next_int(static_cast<uint32_t>(2 * range)) - range),
       r(random.next_int(static_cast<uint32_t>(max_size - min_size)) + min_size)
   {
   }
};

class RandomTree final : public PopObject
{
   random::JavaRandom m_java_random;
   std::vector<LeaveBlob> m_leave_blobs;

   int x_min{}, x_max{};
   int y_min{}, y_max{};
   int z_min{}, z_max{};

   int m_width{}, m_length{}, m_height{};

 public:
   explicit RandomTree(unsigned seed) :
       m_java_random(seed)
   {
      auto big_count   = 1 + m_java_random.next_int(2);
      auto small_count = 3 + m_java_random.next_int(5);

      m_leave_blobs.resize(static_cast<std::size_t>(big_count + small_count));
      std::generate(m_leave_blobs.begin(), m_leave_blobs.begin() + big_count, [this]() {
         return LeaveBlob{m_java_random, 2, 4, 6};
      });
      std::generate(m_leave_blobs.begin() + big_count, m_leave_blobs.end(), [this]() {
         return LeaveBlob{m_java_random, 3, 1, 4};
      });

      x_min = std::numeric_limits<int>::max();
      y_min = std::numeric_limits<int>::max();
      z_min = std::numeric_limits<int>::max();
      x_max = std::numeric_limits<int>::min();
      y_max = std::numeric_limits<int>::min();
      z_max = std::numeric_limits<int>::min();

      for (auto &blob : m_leave_blobs) {
         if ((blob.x - blob.r) < x_min) {
            x_min = (blob.x - blob.r);
         }
         if ((blob.y - blob.r) < y_min) {
            y_min = (blob.y - blob.r);
         }
         if ((blob.z - blob.r) < z_min) {
            z_min = (blob.z - blob.r);
         }
         if ((blob.x + blob.r) > x_max) {
            x_max = (blob.x + blob.r);
         }
         if ((blob.y + blob.r) > y_max) {
            y_max = (blob.y + blob.r);
         }
         if ((blob.z + blob.r) > z_max) {
            z_max = (blob.z + blob.r);
         }
      }

      ++x_max;
      ++y_max;
      ++z_max;

      y_min -= 2;

      m_width  = x_max - x_min;
      m_length = z_max - z_min;
      m_height = y_max - y_min;
   }

   [[nodiscard]] int width() const override
   {
      return m_width;
   }

   [[nodiscard]] int height() const override
   {
      return m_height;
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
   std::unique_ptr<PopObject> create(unsigned int seed) override;
   int occurrence() const override;
};

}// namespace minecpp::world::population

#endif//MINECPP_TREE_H
