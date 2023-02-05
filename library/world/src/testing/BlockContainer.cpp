#include <minecpp/world/testing/BlockContainer.h>

namespace minecpp::world::testing {

BlockContainer::BlockContainer(game::BlockRange range) :
    m_range(range),
    m_blocks(static_cast<std::size_t>(range.block_count()))
{
}

mb::result<game::LightValue> BlockContainer::get_light(game::LightType light_type,
                                                       const game::BlockPosition &pos)
{
   if (not m_range.contains(pos)) {
      return mb::error("not in range");
   }
   return this->access_block_at(pos).light_values[static_cast<std::size_t>(light_type.index())];
}

mb::emptyres BlockContainer::set_light(game::LightType light_type, const game::BlockPosition &pos,
                                       game::LightValue value)
{
   if (not m_range.contains(pos)) {
      return mb::error("not in range");
   }
   this->access_block_at(pos).light_values[static_cast<std::size_t>(light_type.index())] = value;
   ++m_light_changes;
   return mb::ok;
}

mb::result<game::BlockStateId> BlockContainer::get_block(const game::BlockPosition &pos)
{
   if (not m_range.contains(pos)) {
      return mb::error("not in range");
   }
   return this->access_block_at(pos).state;
}

mb::emptyres BlockContainer::set_block(const game::BlockPosition &pos, game::BlockStateId state)
{
   if (not m_range.contains(pos)) {
      return mb::error("not in range");
   }
   this->access_block_at(pos).state = state;
   return mb::ok;
}

BlockContainer::Block &BlockContainer::access_block_at(game::BlockPosition position)
{
   auto distance = position - m_range.min;
   auto x        = static_cast<std::size_t>(distance.x);
   auto y        = static_cast<std::size_t>(distance.y);
   auto z        = static_cast<std::size_t>(distance.z);
   auto width    = static_cast<std::size_t>(m_range.width());
   auto vertical_area =
           static_cast<std::size_t>(m_range.width()) * static_cast<std::size_t>(m_range.height());

   return m_blocks.at(x + y * width + z * vertical_area);
}

mb::emptyres BlockContainer::fill(game::BlockRange range, game::BlockStateId state)
{
   for (auto pos : range) {
      if (auto res = this->set_block(pos, state); res.has_failed())
         return res;
   }
   return mb::ok;
}

mb::emptyres BlockContainer::put_box(game::BlockRange range, game::BlockStateId state)
{
   game::BlockRange wall_back{
           range.min,
           {range.max.x, range.max.y, range.min.z}
   };
   if (auto res = this->fill(wall_back, state); res.has_failed())
      return res;
   game::BlockRange wall_front{
           {range.min.x, range.min.y, range.max.z},
           range.max
   };
   if (auto res = this->fill(wall_front, state); res.has_failed())
      return res;
   game::BlockRange wall_top{
           {range.min.x, range.max.y, range.min.z + 1},
           {range.max.x, range.max.y, range.max.z - 1}
   };
   if (auto res = this->fill(wall_top, state); res.has_failed())
      return res;
   game::BlockRange wall_bottom{
           {range.min.x, range.min.y, range.min.z + 1},
           {range.max.x, range.min.y, range.max.z - 1}
   };
   if (auto res = this->fill(wall_bottom, state); res.has_failed())
      return res;
   game::BlockRange wall_left{
           {range.min.x, range.min.y + 1, range.min.z + 1},
           {range.min.x, range.max.y - 1, range.max.z - 1}
   };
   if (auto res = this->fill(wall_left, state); res.has_failed())
      return res;
   game::BlockRange wall_right{
           {range.max.x, range.min.y + 1, range.min.z + 1},
           {range.max.x, range.max.y - 1, range.max.z - 1}
   };
   if (auto res = this->fill(wall_right, state); res.has_failed())
      return res;
   return mb::ok;
}
}// namespace minecpp::world::testing
