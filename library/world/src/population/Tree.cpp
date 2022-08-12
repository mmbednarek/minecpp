#include <minecpp/repository/Block.h>
#include <minecpp/world/population/Tree.h>

namespace minecpp::world::population {

int RandomTree::block_at(int x, int y, int z) const
{
   const static auto air_id = repository::encode_block_by_tag("minecraft:air");
   const static auto wood_id =
           repository::encode_block_by_tag("minecraft:oak_wood", std::make_pair("axis", "y"));
   const static auto leaves_id =
           repository::encode_block_by_tag("minecraft:oak_leaves", std::make_pair("waterlogged", "false"));
   const static auto stone_id =
           repository::encode_block_by_tag("minecraft:stone");
   const static auto glass_id =
           repository::encode_block_by_tag("minecraft:glass");

   if (x == (m_width / 2) && z == (m_length / 2) && y < 4 * m_height / 5) {
      return wood_id;
   }

   auto xx = x + x_min;
   auto yy = y + y_min;
   auto zz = z + z_min;

   for (auto &blob: m_leave_blobs) {
      int dx = abs(blob.x - xx);
      int dz = abs(blob.y - zz);
      int dy = abs(blob.z - yy);

      auto d = dx * dx + dy * dy + dz * dz;

      if (blob.r == 0 || d < 0)
         continue;

      auto diff = sqrt(d) / static_cast<double>(blob.r);

      if (diff < 1) {
         auto prop = static_cast<int>((1.0 - diff) * 50);
         if (prop == 0 || (rand() % prop == 0)) {
            return air_id;
         }
         if (diff < 0.5) {
            auto prop2 = static_cast<int>((diff) * 40);
            if (prop2 == 0 || (rand() % prop2 == 0)) {
               return wood_id;
            }
         }

         return leaves_id;
      }
   }

   return air_id;
}

PopObject &RandomTreeFactory::create(unsigned int seed)
{
   auto it = m_trees.find(seed);
   if (it != m_trees.end()) {
      return it->second;
   }

   if (m_trees.size() > 20) {
      m_trees.erase(m_trees.begin());
   }

   m_trees.insert({seed, RandomTree(seed)});
   return m_trees.at(seed);
}

int RandomTreeFactory::occurrence() const
{
   return 200;
}

}// namespace minecpp::world::population
