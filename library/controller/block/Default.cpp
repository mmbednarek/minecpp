#include <minecpp/controller/block/Default.h>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/Item.h>
#include <minecpp/util/String.h>

namespace minecpp::controller::block {

bool Default::on_player_place_block(game::World &world, player::Id, game::BlockId block_id,
                                    game::BlockPosition position, game::Face face)
{
   const auto neighbour_position = position.neighbour_at(face);
   const auto source_block_type  = get_source_block_type(world, neighbour_position);
   if (not source_block_type.has_value()) {
      return false;
   }

   auto block = repository::Block::the().get_by_id(block_id);

   game::BlockStateId target_state{};

   if (block->has_state("waterlogged")) {
      target_state = repository::encode_block_state_by_id(
              block_id,
              std::make_pair("waterlogged", util::to_string(*source_block_type == SourceBlockType::Water)));
   } else {
      target_state = repository::StateManager::the().block_base_state(block_id);
   }

   return world.set_block(neighbour_position, target_state).ok();
}

std::optional<game::BlockStateId> Default::on_neighbour_change(game::World &, game::BlockStateId, game::BlockStateId, game::BlockPosition,
                                  game::Face)
{
   return std::nullopt;
}

std::optional<Default::SourceBlockType> Default::get_source_block_type(game::World &world,
                                                                       game::BlockPosition pos)
{
   const auto &block_ids = repository::BlockIds::the();

   auto source_block_state = world.get_block(pos);
   if (source_block_state.has_failed()) {
      return std::nullopt;
   }

   auto [source_block_id, _] = repository::StateManager::the().parse_block_id(*source_block_state);

   if (source_block_id == block_ids.air) {
      return SourceBlockType::Air;
   }

   if (source_block_id == block_ids.water) {
      return SourceBlockType::Water;
   }

   return std::nullopt;
}

bool Default::verify_source_block(game::World &world, game::BlockPosition pos)
{
   const auto source_block_type = get_source_block_type(world, pos);
   return source_block_type.has_value();
}

}// namespace minecpp::controller::block
