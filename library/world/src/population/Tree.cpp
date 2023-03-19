#include <minecpp/repository/Block.h>
#include <minecpp/world/population/Tree.h>

namespace minecpp::world::population {

RandomTree::RandomTree(unsigned int seed) :
    m_java_random(seed)
{
   const auto big_count   = 1 + m_java_random.next_int(2);
   const auto small_count = 3 + m_java_random.next_int(5);
   const auto total_count = big_count + small_count;

   m_leave_blobs.resize(static_cast<std::size_t>(total_count));
   std::generate(m_leave_blobs.begin(), m_leave_blobs.begin() + big_count, [this]() {
      return LeaveBlob{m_java_random, 2, 4, 6};
   });
   std::generate(m_leave_blobs.begin() + big_count, m_leave_blobs.end(), [this]() {
      return LeaveBlob{m_java_random, 3, 1, 4};
   });

   m_min = {
           std::numeric_limits<int>::max(),
           std::numeric_limits<int>::max(),
           std::numeric_limits<int>::max(),
   };

   m_max = {
           std::numeric_limits<int>::min(),
           std::numeric_limits<int>::min(),
           std::numeric_limits<int>::min(),
   };

   for (auto &blob : m_leave_blobs) {
      auto blob_min = blob.position - blob.radius;
      auto blob_max = blob.position + blob.radius;

      m_min = m_min.min(blob_min);
      m_max = m_max.max(blob_max);
   }

   m_max += math::Vector3i{1, 1, 1};
   m_min.set_y(m_min.y() - 3);

   m_extend = m_max - m_min;
}

game::BlockStateId RandomTree::block(const math::Vector3i &position) const
{
   const static auto air_id = repository::encode_block_by_tag("minecraft:air");
   const static auto wood_id =
           repository::encode_block_by_tag("minecraft:oak_wood", std::make_pair("axis", "y"));
   const static auto leaves_id =
           repository::encode_block_by_tag("minecraft:oak_leaves", std::make_pair("waterlogged", "false"));

   const auto center = (m_extend / 2).flat();

   if (position.flat() == center && position.y() < (7 * m_extend.y() / 10)) {
      return wood_id;
   }

   auto absolute_position = position + m_min;

   for (auto &blob : m_leave_blobs) {
      auto distance = (blob.position - absolute_position).cast<float>().length();

      assert(blob.radius != 0);
      assert(distance >= 0.0f);

      auto normalized_distance = distance / static_cast<float>(blob.radius);

      if (normalized_distance < 1.0f) {
         auto prop = static_cast<mb::u32>(50.0f * (1.0f - normalized_distance));
         if (prop == 0 || (m_java_random.next_int(prop) == 0)) {
            return air_id;
         }

         if (normalized_distance < 0.5) {
            auto prop2 = static_cast<mb::u32>(40.0f * normalized_distance);
            if (prop2 == 0 || (m_java_random.next_int(prop2) == 0)) {
               return wood_id;
            }
         }

         return leaves_id;
      }
   }

   return air_id;
}

math::Vector3i RandomTree::extent() const
{
   return m_extend;
}

math::Vector2i RandomTree::center() const
{
   return m_extend.flat() / 2;
}

std::unique_ptr<PopObject> RandomTreeFactory::create(unsigned int seed)
{
   return std::make_unique<RandomTree>(seed);
}

int RandomTreeFactory::occurrence() const
{
   return 200;
}

}// namespace minecpp::world::population
