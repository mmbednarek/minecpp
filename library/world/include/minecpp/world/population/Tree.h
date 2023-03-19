#ifndef MINECPP_TREE_H
#define MINECPP_TREE_H

#pragma once

#include "Object.h"
#include <minecpp/random/JavaRandom.h>
#include <unordered_map>

namespace minecpp::world::population {

struct LeaveBlob
{
   math::Vector3i position;
   int radius;

   LeaveBlob() = default;

   explicit LeaveBlob(random::JavaRandom &random, int range, int min_size, int max_size) :
       position{
               random.next_int(static_cast<uint32_t>(2 * range)) - range,
               random.next_int(static_cast<uint32_t>(2 * range)) - range,
               random.next_int(static_cast<uint32_t>(2 * range)) - range,
       },
       radius(random.next_int(static_cast<uint32_t>(max_size - min_size)) + min_size)
   {
   }
};

class RandomTree final : public PopObject
{
   mutable random::JavaRandom m_java_random;
   std::vector<LeaveBlob> m_leave_blobs;

   math::Vector3i m_min{};
   math::Vector3i m_max{};
   math::Vector3i m_extend{};

 public:
   explicit RandomTree(unsigned seed);

   [[nodiscard]] math::Vector3i extent() const override;
   [[nodiscard]] math::Vector2i center() const override;

   [[nodiscard]] game::BlockStateId block(const math::Vector3i &position) const override;
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
