#include <minecpp/game/worldgen/population/Tree.h>
#include <minecpp/repository/Block.h>

namespace minecpp::game::worldgen::population {

int RandomTree::block_at(int x, int y, int z) const
{
   const static auto air_id = repository::encode_block_by_tag("minecraft:air");
   const static auto wood_id =
           repository::encode_block_by_tag("minecraft:oak_wood", std::make_pair("axis", "y"));
   const static auto leaves_id = repository::encode_block_by_tag("minecraft:oak_leaves", std::make_pair("waterlogged", "false"));

   //   return wood_id;

   if (x == (m_width / 2) && z == (m_length / 2) && y < 4 * m_height / 5) {
      return wood_id;
   }

   auto xx = x + x_min;
   auto yy = y + y_min - 2;
   auto zz = z + z_min;

   int dx1 = abs(x1 - xx);
   int dz1 = abs(z1 - zz);
   int dy1 = abs(y1 - yy);
   auto d1 = dx1 * dx1 + dy1 * dy1 + dz1 * dz1;

   int dx2 = abs(x2 - xx);
   int dz2 = abs(z2 - zz);
   int dy2 = abs(y2 - yy);
   auto d2 = dx2 * dx2 + dy2 * dy2 + dz2 * dz2;

   int dx3 = abs(x3 - xx);
   int dz3 = abs(z3 - zz);
   int dy3 = abs(y3 - yy);
   auto d3 = dx3 * dx3 + dy3 * dy3 + dz3 * dz3;

   if (d1 < r1 * r1 || d2 < r2 * r2 || d3 < r3 * r3) {
      if (d1 < r1 * r1 / 2 || d2 < r2 * r2 / 2 || d3 < r3 * r3 / 2) {
         if ((rand() % 5) == 0) {
            return wood_id;
         }
      }

      return leaves_id;
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

int RandomTreeFactory::occurrence() const { return 200; }

}// namespace minecpp::game::worldgen::population
