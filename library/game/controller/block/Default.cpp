#include <minecpp/game/controller/block/Default.h>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/Item.h>

namespace minecpp::game::controller::block {

bool Default::on_player_place_block(World &world, player::Id, int block_id, BlockPosition position,
                                    Face face)
{
   auto neighbour_position = position.neighbour_at(face);

   auto source_block_state = world.get_block(neighbour_position);
   if (source_block_state.has_failed()) {
      return false;
   }

   const auto air_id = static_cast<int>(repository::Block::the().find_id_by_tag("minecraft:air").unwrap(0));
   const auto water_id =
           static_cast<int>(repository::Block::the().find_id_by_tag("minecraft:water").unwrap(0));

   auto [source_block_id, _] = repository::StateManager::the().parse_block_id(*source_block_state);
   if (source_block_id != air_id && source_block_id != water_id) {
      return false;
   }

   auto block = repository::Block::the().get_by_id(static_cast<unsigned long>(block_id));
   auto state = repository::StateManager::the().block_base_state(block_id);

   if (block->find_state("waterlogged") != std::nullopt) {
      if (source_block_id == water_id) {
         state = repository::encode_block_by_tag(block->tag(), std::make_pair("waterlogged", "true"));
      } else {
         state = repository::encode_block_by_tag(block->tag(), std::make_pair("waterlogged", "false"));
      }
   }

   return world.set_block(neighbour_position, state).ok();
}

}// namespace minecpp::game::controller::block
