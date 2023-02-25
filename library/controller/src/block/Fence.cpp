#include "minecpp/repository/Block.h"
#include <minecpp/controller/block/Fence.h>
#include <minecpp/util/String.h>

namespace minecpp::controller::block {

namespace {
bool is_fence_block(game::BlockStateId state_id)
{
   auto [block_id, _] = repository::StateManager::the().parse_block_id(state_id);

   // TODO: Find a better way to do this
   auto block = repository::Block::the().get_by_id(block_id);
   if (block.has_failed())
      return false;

   return block->tag().ends_with("_fence");
}

bool is_fence_at_pos(game::IWorld &world, game::BlockPosition pos)
{
   auto state = world.get_block(pos);
   if (state.has_failed())
      return false;
   return is_fence_block(*state);
}

}// namespace

bool Fence::on_player_place_block(game::IWorld &world, game::PlayerId, game::BlockId block_id,
                                  game::BlockPosition position, game::Face face)
{
   auto pos = position.neighbour_at(face);

   auto east  = is_fence_at_pos(world, pos.neighbour_at(game::Face::East));
   auto west  = is_fence_at_pos(world, pos.neighbour_at(game::Face::West));
   auto north = is_fence_at_pos(world, pos.neighbour_at(game::Face::North));
   auto south = is_fence_at_pos(world, pos.neighbour_at(game::Face::South));

   const auto source_block_type = get_source_block_type(world, pos);
   if (not source_block_type.has_value()) {
      return false;
   }

   auto waterlogged = (*source_block_type == SourceBlockType::Water);

   auto state = repository::encode_block_state_by_id(
           block_id, std::make_pair("waterlogged", util::to_string(waterlogged)),
           std::make_pair("east", util::to_string(east)), std::make_pair("west", util::to_string(west)),
           std::make_pair("north", util::to_string(north)), std::make_pair("south", util::to_string(south)));

   return world.set_block(pos, state).ok();
}

std::optional<game::BlockStateId> Fence::on_neighbour_change(game::IWorld &,
                                                             game::BlockStateId block_state_id,
                                                             game::BlockStateId neighbour_block_state_id,
                                                             game::BlockPosition, game::Face face)
{
   if (face == game::Face::Top || face == game::Face::Bottom)
      return std::nullopt;

   auto [block_id, block_state] = repository::StateManager::the().parse_block_id(block_state_id);
   auto block                   = repository::Block::the().get_by_id(block_id);
   if (block.has_failed())
      return std::nullopt;

   auto is_fence = is_fence_block(neighbour_block_state_id);
   return repository::set_state(block_id, block_state, face.to_string(), util::to_string(is_fence));
}

}// namespace minecpp::controller::block
