#include <minecpp/controller/block/Default.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Location.h>
#include <minecpp/game/IEntitySystem.hpp>
#include <minecpp/game/player/Player.h>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/Item.h>
#include <minecpp/util/String.h>
#include <minecpp/world/BlockState.h>

using minecpp::game::Face;
using minecpp::game::HalfPlacement;
using minecpp::world::BlockState;

namespace minecpp::controller::block {

bool Default::on_player_place_block(game::IWorld &world, game::PlayerId, int block_id,
                                    game::BlockPosition position, game::Face face,
                                    const math::Vector3f & /*crosshair_position*/)
{
   const auto neighbour_position = position.neighbour_at(face);

   game::BlockStateId target_state_id{};

   auto block = repository::Block::the().get_by_id(block_id);
   if (block->has_state("waterlogged")) {
      const auto source_block_type = get_source_block_type(world, neighbour_position);
      if (not source_block_type.has_value())
         return false;

      BlockState target_state(block_id, 0);
      target_state.set("waterlogged", *source_block_type == SourceBlockType::Water);
      target_state_id = target_state.block_state_id();
   } else {
      target_state_id = repository::StateManager::the().block_base_state(block_id);
   }

   return world.set_block(neighbour_position, target_state_id).ok();
}

std::optional<game::BlockStateId> Default::on_neighbour_change(game::IWorld &, game::BlockStateId,
                                                               game::BlockStateId, game::BlockPosition,
                                                               game::Face)
{
   return std::nullopt;
}

bool Default::on_player_action(game::IWorld &world, game::PlayerId player_id,
                               game::BlockStateId block_state_id, game::BlockPosition position,
                               game::Face face, const math::Vector3f &crosshair_position)
{
   return false;
}

std::optional<Default::SourceBlockType> Default::get_source_block_type(game::IWorld &world,
                                                                       game::BlockPosition pos)
{
   const auto &block_ids = repository::BlockIds::the();

   auto source_block_state = world.get_block(pos);
   if (source_block_state.has_failed()) {
      return std::nullopt;
   }

   auto [source_block_id, _] = repository::StateManager::the().parse_block_id(*source_block_state);

   if (source_block_id == block_ids.Air) {
      return SourceBlockType::Air;
   }

   if (source_block_id == block_ids.Water) {
      return SourceBlockType::Water;
   }

   return std::nullopt;
}

bool Default::verify_source_block(game::IWorld &world, game::BlockPosition pos)
{
   const auto source_block_type = get_source_block_type(world, pos);
   return source_block_type.has_value();
}

std::optional<game::Direction> Default::find_player_direction(game::IWorld &world, game::PlayerId player_id,
                                                              game::BlockPosition position)
{
   auto player = world.players().get_player(player_id);
   if (player.has_failed())
      return std::nullopt;

   if (not player->is_alive())
      return std::nullopt;

   auto player_entity = world.entity_system().entity(player->entity_id());
   if (not player_entity.is_valid())
      return std::nullopt;

   if (not player_entity.has_component<LocationComponent>())
      return std::nullopt;

   const auto block_position  = position.to_vec3().flat() + math::Vector2{0.5, 0.5};
   const auto player_position = player_entity.component<LocationComponent>().position().flat();
   return game::Direction::from_vec2(block_position - player_position);
}

bool Default::verify_source_is_air(game::IWorld &world, game::BlockPosition pos)
{
   return get_source_block_type(world, pos) == SourceBlockType::Air;
}

HalfPlacement Default::deduce_half_placement(Face face, float y)
{
   if (face == Face::Bottom)
      return HalfPlacement::Top;
   if (face == Face::Top)
      return HalfPlacement::Bottom;
   if (y > 0.5f)
      return HalfPlacement::Top;
   return HalfPlacement::Bottom;
}

}// namespace minecpp::controller::block

// namespace minecpp::controller::block
