#include "minecpp/repository/Block.h"
#include <minecpp/controller/block/Door.h>

namespace minecpp::controller::block {

namespace {
game::Direction direction_to_face_direction(game::Direction  dir) {
   switch (dir) {
   case game::Direction::West: return game::Direction::South;
   case game::Direction::East: return game::Direction::North;
   case game::Direction::South: return game::Direction::East;
   case game::Direction::North: return game::Direction::West;
   }

   return game::Direction::North;
}
}

bool Door::on_player_place_block(game::World &world, player::Id player_id, game::BlockId block_id,
                                 game::BlockPosition position, game::Face face)
{
   auto player = world.players().get_player(player_id);
   if (player.has_failed())
      return false;

   auto player_entity = world.entities().get_entity(player->entity_id());
   if (player_entity.has_failed())
      return false;

   auto lower_pos = position.neighbour_at(face);
   auto upper_pos = lower_pos;
   ++upper_pos.y;

   if (not verify_source_block(world, lower_pos))
      return false;

   if (not verify_source_block(world, upper_pos))
      return false;

   const auto block_pos = lower_pos.to_vec3().flat();
   const auto direction = direction_to_face_direction(game::direction_from_vec2(block_pos - player_entity->get_pos().flat()));
   const auto direction_str = game::to_string(direction);

   auto block = repository::Block::the().get_by_id(block_id);
   auto lower_state = repository::encode_block_by_tag(block->tag(), std::make_pair("half", "lower"), std::make_pair("facing", direction_str));

   if (world.set_block(lower_pos, lower_state).has_failed())
      return false;

   auto upper_state = repository::encode_block_by_tag(block->tag(), std::make_pair("half", "upper"), std::make_pair("facing", direction_str));

   return world.set_block(upper_pos, upper_state).ok();
}
}
