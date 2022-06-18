#include "minecpp/repository/Block.h"
#include <minecpp/controller/block/Torch.h>
#include <spdlog/spdlog.h>

namespace minecpp::controller::block {

bool Torch::on_player_place_block(game::World &world, game::PlayerId player_id, game::BlockId block_id,
                                  game::BlockPosition position, game::Face face)
{
   if (face == game::Face::Bottom)
      return false;

   auto torch_pos = position.neighbour_at(face);

   const auto source_block_type = get_source_block_type(world, torch_pos);
   if (not source_block_type.has_value())
      return false;
   if (*source_block_type != SourceBlockType::Air)
      return false;

   auto &block_ids = repository::BlockIds::the();

   if (face == game::Face::Top) {
      return world.set_block(torch_pos, repository::StateManager::the().block_base_state(block_ids.torch))
              .ok();
   }

   auto state = repository::encode_block_state_by_id(block_ids.wall_torch,
                                                     std::make_pair("facing", game::to_string(face)));
   return world.set_block(torch_pos, state).ok();
}

std::optional<game::BlockStateId> Torch::on_neighbour_change(game::World &world,
                                                             game::BlockStateId block_state_id,
                                                             game::BlockStateId neighbour_block_state_id,
                                                             game::BlockPosition position, game::Face face)
{
   game::Face connected_face{};

   auto &block_ids = repository::BlockIds::the();

   auto [block_id, state_id] = repository::StateManager::the().parse_block_id(block_state_id);
   if (block_id == block_ids.torch) {
      connected_face = game::Face::Bottom;
   } else {
      auto block     = repository::Block::the().get_by_id(block_id);
      connected_face = game::opposite_face(
              game::parse_face(block->state_value("facing", state_id)).value_or(game::Face::Bottom));
   }

   if (connected_face == face)
      return block_ids.air;

   return std::nullopt;
}

}// namespace minecpp::controller::block
