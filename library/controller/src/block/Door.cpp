#include <minecpp/controller/block/Door.h>
#include <minecpp/repository/Block.h>
#include <minecpp/world/BlockState.h>

namespace minecpp::controller::block {

using game::BlockId;
using game::BlockPosition;
using game::BlockStateId;
using game::Direction;
using game::Face;
using game::Half;
using game::IWorld;
using game::PlayerId;
using game::Side;
using world::BlockState;

static bool check_side(IWorld &world, BlockPosition pos, Direction dir, Side side, BlockId door_id);

static Side find_side(IWorld &world, BlockPosition upper, BlockPosition lower, Direction dir,
                      BlockId door_id);

bool Door::on_player_place_block(IWorld &world, PlayerId player_id, BlockId block_id, BlockPosition position,
                                 Face face)
{
   auto lower_pos = position.neighbour_at(face);
   auto upper_pos = lower_pos.neighbour_at(Face::Top);

   if (not verify_source_block(world, lower_pos) || not verify_source_block(world, upper_pos))
      return false;

   const auto player_direction = find_player_direction(world, player_id, lower_pos);
   if (not player_direction.has_value())
      return false;

   auto door_direction = player_direction->turn(Side::Left);

   auto hinge_side = find_side(world, upper_pos, lower_pos, *player_direction, block_id);
   if (hinge_side == Side::Right)
      door_direction = game::opposite_direction(door_direction);

   BlockState lower_state{block_id, 0};
   lower_state.set<Half>("half", Half::Lower);
   lower_state.set<Side>("hinge", hinge_side);
   lower_state.set<Direction>("facing", door_direction);

   if (world.set_block(lower_pos, lower_state.block_state_id()).has_failed())
      return false;

   BlockState upper_state{block_id, 0};
   upper_state.set<Half>("half", Half::Upper);
   upper_state.set<Side>("hinge", hinge_side);
   upper_state.set<Direction>("facing", door_direction);

   return world.set_block(upper_pos, upper_state.block_state_id()).ok();
}

std::optional<BlockStateId> Door::on_neighbour_change(IWorld & /*world*/, BlockStateId block_state_id,
                                                      BlockStateId neighbour_block_state_id,
                                                      BlockPosition /*position*/, Face face)
{
   BlockState state{block_state_id};

   auto half = state.get<Half>("half");
   if (not half.has_value())
      return std::nullopt;

   auto corresponding_face = (*half == Half::Lower) ? Face::Top : Face::Bottom;
   if (face != corresponding_face)
      return std::nullopt;

   BlockState other_half_state{neighbour_block_state_id};

   if (other_half_state.block_id() != state.block_id())
      return BLOCK_ID(Air);

   other_half_state.set<Half>("half", *half);

   return other_half_state.block_state_id();
}

bool Door::on_player_action(IWorld &world, PlayerId /*player_id*/, BlockStateId block_state_id,
                            BlockPosition position, Face /*face*/, math::Vector3 /*crosshair_position*/)
{
   BlockState state{block_state_id};
   auto open = state.get<bool>("open");
   if (not open.has_value()) {
      return false;
   }

   state.set("open", not(*open));

   return world.set_block(position, state.block_state_id()).ok();
}

bool check_side(IWorld &world, BlockPosition pos, Direction dir, Side side, BlockId door_id)
{
   auto block = world.get_block(pos.neighbour_at(dir.turn(side).to_face()));
   if (block.has_failed())
      return false;

   BlockState state{*block};

   return state.block_id() != BLOCK_ID(Air) && state.block_id() != door_id;
}

Side find_side(IWorld &world, BlockPosition upper, BlockPosition lower, Direction dir, BlockId door_id)
{
   if (check_side(world, upper, dir, Side::Right, door_id))
      return Side::Left;
   if (check_side(world, lower, dir, Side::Right, door_id))
      return Side::Left;

   if (check_side(world, upper, dir, Side::Left, door_id))
      return Side::Right;
   if (check_side(world, lower, dir, Side::Left, door_id))
      return Side::Right;

   return Side::Right;
}

}// namespace minecpp::controller::block
