#include <minecpp/game/worldgen/population/object.h>
#include <minecpp/repository/block.h>

namespace minecpp::game::worldgen::population {

ObjectRepository ObjectRepository::g_instance;

void ObjectRepository::register_objects()
{
   int air_id     = repository::encode_block_by_tag("minecraft:air");
   int stone_id   = repository::encode_block_by_tag("minecraft:stone");
   int wood_id    = repository::encode_block_by_tag("minecraft:oak_wood", std::make_pair("axis", "y"));
   int leaves_id  = repository::encode_block_by_tag("minecraft:oak_leaves");
   int pumpkin_id = repository::encode_block_by_tag("minecraft:pumpkin");
   int tall_grass_upper_id =
           repository::encode_block_by_tag("minecraft:tall_grass", std::make_pair("half", "upper"));
   int tall_grass_lower_id =
           repository::encode_block_by_tag("minecraft:tall_grass", std::make_pair("half", "lower"));
   int dendelion_id   = repository::encode_block_by_tag("minecraft:dandelion");
   int poppy_id       = repository::encode_block_by_tag("minecraft:poppy");
   int blue_orchid_id = repository::encode_block_by_tag("minecraft:blue_orchid");

   m_objects.push_back(std::make_unique<ShapedObject<5, 5, 7>>(
           300,
           std::array<int, 5 * 5 * 7>{
                   air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    wood_id,   air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    wood_id,   air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    wood_id,   air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, wood_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, air_id,    leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                   wood_id,   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id, air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    leaves_id, leaves_id, leaves_id, air_id,    air_id,
                   leaves_id, leaves_id, leaves_id, air_id,    air_id,    leaves_id, leaves_id, leaves_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    leaves_id, air_id,    air_id,
                   air_id,    leaves_id, leaves_id, leaves_id, air_id,    air_id,    air_id,    leaves_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,    air_id,    air_id,
           }));

   m_objects.push_back(std::make_unique<ShapedObject<1, 1, 1>>(5,// per 10 000 elements
                                                               std::array<int, 1 * 1 * 1>{
                                                                       pumpkin_id,
                                                               }));

   m_objects.push_back(
           std::make_unique<ShapedObject<1, 1, 1>>(1800,// per 10 000 elements
                                                   std::array<int, 1 * 1 * 1>{tall_grass_upper_id}));

   m_objects.push_back(std::make_unique<ShapedObject<1, 1, 2>>(500,// per 10 000 elements
                                                               std::array<int, 1 * 1 * 2>{
                                                                       tall_grass_lower_id,
                                                                       tall_grass_upper_id,
                                                               }));

   m_objects.push_back(std::make_unique<ShapedObject<1, 1, 1>>(100,// per 10 000 elements
                                                               std::array<int, 1 * 1 * 1>{dendelion_id}));

   m_objects.push_back(std::make_unique<ShapedObject<1, 1, 1>>(100,// per 10 000 elements
                                                               std::array<int, 1 * 1 * 1>{poppy_id}));

   m_objects.push_back(std::make_unique<ShapedObject<1, 1, 1>>(15,// per 10 000 elements
                                                               std::array<int, 1 * 1 * 1>{blue_orchid_id}));
}

mb::size ObjectRepository::find_object_id(int value)
{
   if (value == 0) {
      return 0;
   }
   mb::size i = 0;
   for (const auto &e : m_objects) {
      value -= e->occurrence();
      if (value <= 0) {
         break;
      }
      ++i;
   }

   if (i == m_objects.size()) {
      return -1;
   }

   return i;
}

}// namespace minecpp::game::worldgen::population
