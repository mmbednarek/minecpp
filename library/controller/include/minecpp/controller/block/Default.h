#ifndef MINECPP_DEFAULTCONTROLLER_H
#define MINECPP_DEFAULTCONTROLLER_H
#include <minecpp/game/IBlockController.hpp>
#include <minecpp/game/property/Direction.h>
#include <minecpp/game/property/Face.h>
#include <minecpp/game/property/HalfPlacement.hpp>
#include <optional>

namespace minecpp::controller::block {

class Default : public game::IBlockController
{
 public:
   bool on_player_place_block(game::IWorld &world, game::PlayerId player_id, game::BlockId block_id,
                              game::BlockPosition position, game::Face face,
                              const math::Vector3f &crosshair_position) override;

   std::optional<game::BlockStateId> on_neighbour_change(game::IWorld &world,
                                                         game::BlockStateId block_state_id,
                                                         game::BlockStateId neighbour_block_state_id,
                                                         game::BlockPosition position,
                                                         game::Face face) override;

   bool on_player_action(game::IWorld &world, game::PlayerId player_id, game::BlockStateId block_state_id,
                         game::BlockPosition position, game::Face face,
                         const math::Vector3f &crosshair_position) override;

 protected:
   enum class SourceBlockType
   {
      Air,
      Water
   };

   [[nodiscard]] static std::optional<SourceBlockType> get_source_block_type(game::IWorld &world,
                                                                             game::BlockPosition pos);
   [[nodiscard]] static bool verify_source_block(game::IWorld &world, game::BlockPosition pos);
   [[nodiscard]] static bool verify_source_is_air(game::IWorld &world, game::BlockPosition pos);
   [[nodiscard]] static std::optional<game::Direction>
   find_player_direction(game::IWorld &world, game::PlayerId player_id, game::BlockPosition position);

   [[nodiscard]] static game::HalfPlacement deduce_half_placement(game::Face face, float y);
};

}// namespace minecpp::controller::block

#endif//MINECPP_DEFAULTCONTROLLER_H
