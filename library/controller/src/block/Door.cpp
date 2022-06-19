#include "minecpp/repository/Block.h"
#include "minecpp/util/String.h"
#include <minecpp/controller/block/Door.h>
#include <spdlog/spdlog.h>

namespace minecpp::controller::block {

namespace {
game::Direction direction_to_face_direction(game::Direction dir)
{
   switch (dir) {
   case game::Direction::West: return game::Direction::South;
   case game::Direction::East: return game::Direction::North;
   case game::Direction::South: return game::Direction::East;
   case game::Direction::North: return game::Direction::West;
   }

   return game::Direction::North;
}
}// namespace

bool Door::on_player_place_block(game::World &world, game::PlayerId player_id, game::BlockId block_id,
                                 game::BlockPosition position, game::Face face)
{
   auto lower_pos = position.neighbour_at(face);
   auto upper_pos = lower_pos;
   ++upper_pos.y;

   if (not verify_source_block(world, lower_pos))
      return false;

   if (not verify_source_block(world, upper_pos))
      return false;

   const auto player_direction = find_player_direction(world, player_id, lower_pos);
   if (not player_direction.has_value())
      return false;

   auto door_direction = direction_to_face_direction(*player_direction);

   game::Side hinge_side{find_side(world, upper_pos, lower_pos, *player_direction, block_id)};
   if (hinge_side == game::Side::Right)
      door_direction = game::opposite_direction(door_direction);

   const auto direction_str = game::to_string(door_direction);

   auto lower_state = repository::encode_block_state_by_id(block_id, std::make_pair("half", "lower"), std::make_pair("hinge", game::to_string(hinge_side)),
                                                           std::make_pair("facing", direction_str));

   if (world.set_block(lower_pos, lower_state).has_failed())
      return false;

   auto upper_state = repository::encode_block_state_by_id(block_id, std::make_pair("half", "upper"), std::make_pair("hinge", game::to_string(hinge_side)),
                                                           std::make_pair("facing", direction_str));

   return world.set_block(upper_pos, upper_state).ok();
}

std::optional<game::BlockStateId> Door::on_neighbour_change(game::World &world,
                                                            game::BlockStateId block_state_id,
                                                            game::BlockStateId neighbour_block_state_id,
                                                            game::BlockPosition position, game::Face face)
{
   auto [block_id, state_id] = repository::StateManager::the().parse_block_id(block_state_id);
   auto block                = repository::Block::the().get_by_id(block_id);
   if (block.has_failed())
      return std::nullopt;

   auto half = block->state_value("half", state_id);

   if (half == "lower") {
      if (face != game::Face::Top)
         return std::nullopt;
   } else if (half == "upper") {
      if (face != game::Face::Bottom)
         return std::nullopt;
   } else {
      return std::nullopt;
   }

   auto [other_half_block_id, other_half_state_id] =
           repository::StateManager::the().parse_block_id(neighbour_block_state_id);

   if (other_half_block_id != block_id)
      return repository::BlockIds::the().air;

   return repository::set_state(block_id, other_half_state_id, "half", half);
}

bool Door::on_player_action(game::World &world, game::PlayerId player_id, game::BlockStateId block_state_id,
                            game::BlockPosition position, game::Face face, util::Vec3 crosshair_position)
{
   const auto [block_id, state_id] = repository::StateManager::the().parse_block_id(block_state_id);
   auto block                = repository::Block::the().get_by_id(block_id);
   if (block.has_failed())
      return false;

   const auto open_str = block->state_value("open", state_id);
   const auto open = open_str == "true";

   auto state = repository::set_state(block_id, state_id, "open", util::to_string(not open));
   if (not state.has_value())
      return false;

   return world.set_block(position, *state).ok();
}

game::Side Door::find_side(game::World &world, game::BlockPosition upper, game::BlockPosition lower, game::Direction dir, game::BlockId door_id)
{
   if (check_side(world, upper, dir, game::Side::Right, door_id))
      return game::Side::Left;
   if (check_side(world, lower, dir, game::Side::Right, door_id))
      return game::Side::Left;

   if (check_side(world, upper, dir, game::Side::Left, door_id))
      return game::Side::Right;
   if (check_side(world, lower, dir, game::Side::Left, door_id))
      return game::Side::Right;

   return game::Side::Right;
}

bool Door::check_side(game::World &world, game::BlockPosition pos, game::Direction dir, game::Side side, game::BlockId door_id)
{
   auto block = world.get_block(pos.neighbour_at(game::direction_to_face(game::direction_at(dir, side).value_or(game::Direction::North)).value_or(game::Face::North)));
   if (block.has_failed())
      return false;

   auto [block_id, _] = repository::StateManager::the().parse_block_id(*block);

   auto ids = repository::BlockIds::the();

   return block_id != ids.air && block_id != door_id;
}

}// namespace minecpp::controller::block
