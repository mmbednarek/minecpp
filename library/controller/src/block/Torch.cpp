#include <minecpp/controller/block/Torch.h>
#include <minecpp/repository/Block.h>
#include <minecpp/world/BlockState.h>

namespace minecpp::controller::block {

using game::BlockId;
using game::BlockPosition;
using game::Face;
using game::IWorld;
using game::LightType;
using game::PlayerId;
using world::BlockState;

static std::optional<Face> find_connected_face(const BlockState &state);

bool Torch::on_player_place_block(IWorld &world, PlayerId /*player_id*/, BlockId /*block_id*/,
                                  BlockPosition position, Face place_face)
{
   // Cannot place torch on a ceiling
   if (place_face == Face::Bottom)
      return false;

   // Find the position where torch should be placed
   auto torch_pos = position.neighbour_at(place_face);

   // Torch can be placed only within an air block
   if (not verify_source_is_air(world, torch_pos))
      return false;

   // Update the light value
   world.light_system().add_light_source(torch_pos, 15);

   // If we're placing the torch on a floor we should place minecraft:torch
   if (place_face == Face::Top) {
      return world.set_block(torch_pos, DEFAULT_BLOCK_STATE(Torch)).ok();
   }

   // Create new wall torch state and set facing to the same we are placing it
   BlockState state(BLOCK_ID(WallTorch), 0);
   state.set("facing", place_face);

   // Set the final state id
   return world.set_block(torch_pos, state.block_state_id()).ok();
}

std::optional<game::BlockStateId> Torch::on_neighbour_change(game::IWorld &world,
                                                             game::BlockStateId block_state_id,
                                                             game::BlockStateId neighbour_block_state_id,
                                                             game::BlockPosition position, game::Face face)
{
   auto connected_face = find_connected_face(BlockState{block_state_id});

   // If the block on the connected face of the torch has been changed
   // we need to replace it with air
   if (connected_face.has_value() && *connected_face == face)
      return BLOCK_ID(Air);

   return std::nullopt;
}

std::optional<Face> find_connected_face(const BlockState &state)
{
   if (state.block_id() == BLOCK_ID(Torch))
      return Face::Bottom;

   return state.get<Face>("facing");
};

}// namespace minecpp::controller::block
