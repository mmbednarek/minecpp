#include "minecpp/repository/Block.h"
#include <minecpp/controller/block/Stairs.h>
#include <minecpp/util/String.h>

namespace minecpp::controller::block {

bool Stairs::on_player_place_block(game::IWorld &world, game::PlayerId player_id, game::BlockId block_id,
                                   game::BlockPosition position, game::Face face)
{
   auto pos = position.neighbour_at(face);

   const auto source_block_type = get_source_block_type(world, pos);
   if (not source_block_type.has_value()) {
      return false;
   }

   const auto player_direction = find_player_direction(world, player_id, pos);
   if (not player_direction.has_value())
      return false;

   auto waterlogged = (*source_block_type == SourceBlockType::Water);

   auto state =
           repository::encode_block_state_by_id(block_id, std::make_pair("half", "bottom"),
                                                std::make_pair("facing", game::to_string(*player_direction)),
                                                std::make_pair("waterlogged", util::to_string(waterlogged)));
   return world.set_block(pos, state).ok();
}

}// namespace minecpp::controller::block
