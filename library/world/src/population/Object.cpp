#include <minecpp/repository/Block.h>
#include <minecpp/world/population/Object.h>
#include <minecpp/world/population/Tree.h>

namespace minecpp::world::population {

ObjectRepository ObjectRepository::s_instance;

template<typename T, typename... TArgs>
std::unique_ptr<StaticObjectFactory> make_simple_object(int occurrence, TArgs &&...args)
{
   return std::make_unique<StaticObjectFactory>(occurrence,
                                                std::make_unique<T>(std::forward<TArgs>(args)...));
}

void ObjectRepository::register_objects()
{
   auto air_id  = repository::encode_block_by_tag("minecraft:air");
   auto wood_id = repository::encode_block_by_tag("minecraft:oak_wood", std::make_pair("axis", "y"));
   auto leaves_id =
           repository::encode_block_by_tag("minecraft:oak_leaves", std::make_pair("waterlogged", "false"));
   auto pumpkin_id = repository::encode_block_by_tag("minecraft:pumpkin");
   auto tall_grass_upper_id =
           repository::encode_block_by_tag("minecraft:tall_grass", std::make_pair("half", "upper"));
   auto tall_grass_lower_id =
           repository::encode_block_by_tag("minecraft:tall_grass", std::make_pair("half", "lower"));
   auto dandelion_id   = repository::encode_block_by_tag("minecraft:dandelion");
   auto poppy_id       = repository::encode_block_by_tag("minecraft:poppy");
   auto blue_orchid_id = repository::encode_block_by_tag("minecraft:blue_orchid");

   m_objects.push_back(make_simple_object<ShapedObject<5, 5, 7>>(
           300, std::array<game::BlockStateId, 5 * 5 * 7>{
                        // clang-format off
                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    wood_id,   air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,

                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    wood_id,   air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,

                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    wood_id,   air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,

                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, wood_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,

                   air_id,    leaves_id, leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, wood_id,   leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                   leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,

                   air_id,    air_id,    air_id,    air_id,    air_id,
                   air_id,    leaves_id, leaves_id, leaves_id, air_id,
                   air_id,    leaves_id, leaves_id, leaves_id, air_id,
                   air_id,    leaves_id, leaves_id, leaves_id, air_id,
                   air_id,    air_id,    air_id,    air_id,    air_id,

                   air_id,    air_id,     air_id,     air_id,    air_id,
                   air_id,    air_id,    leaves_id,   air_id,    air_id,
                   air_id,    leaves_id, leaves_id,   leaves_id, air_id,
                   air_id,    air_id,    leaves_id,   air_id,    air_id,
                   air_id,    air_id,    air_id,      air_id,    air_id,
                        // clang-format on
                }));

   m_objects.push_back(make_simple_object<ShapedObject<1, 1, 1>>(5,// per 10 000 elements
                                                                 std::array<game::BlockStateId, 1 * 1 * 1>{
                                                                         pumpkin_id,
                                                                 }));

   m_objects.push_back(make_simple_object<ShapedObject<1, 1, 1>>(
           1800,// per 10 000 elements
           std::array<game::BlockStateId, 1 * 1 * 1>{tall_grass_upper_id}));

   m_objects.push_back(make_simple_object<ShapedObject<1, 1, 2>>(500,// per 10 000 elements
                                                                 std::array<game::BlockStateId, 1 * 1 * 2>{
                                                                         tall_grass_lower_id,
                                                                         tall_grass_upper_id,
                                                                 }));

   m_objects.push_back(make_simple_object<ShapedObject<1, 1, 1>>(
           100,// per 10 000 elements
           std::array<game::BlockStateId, 1 * 1 * 1>{dandelion_id}));

   m_objects.push_back(
           make_simple_object<ShapedObject<1, 1, 1>>(100,// per 10 000 elements
                                                     std::array<game::BlockStateId, 1 * 1 * 1>{poppy_id}));

   m_objects.push_back(make_simple_object<ShapedObject<1, 1, 1>>(
           15,// per 10 000 elements
           std::array<game::BlockStateId, 1 * 1 * 1>{blue_orchid_id}));

   m_objects.push_back(std::make_unique<RandomTreeFactory>());
}

std::optional<std::size_t> ObjectRepository::find_object_id(int value)
{
   if (value == 0)
      return 0;

   mb::size i = 0;
   for (const auto &e : m_objects) {
      value -= e->occurrence();
      if (value <= 0) {
         break;
      }
      ++i;
   }

   if (i == m_objects.size())
      return std::nullopt;

   return i;
}

}// namespace minecpp::world::population
