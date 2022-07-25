#ifndef MINECPP_DEFAULTCONTROLLER_H
#define MINECPP_DEFAULTCONTROLLER_H
#include <minecpp/controller/BlockController.hpp>
#include <optional>

namespace minecpp::controller::block {

class Default : public BlockController
{
 public:
   bool on_player_place_block(game::World &world, game::PlayerId player_id, game::BlockId block_id,
                              game::BlockPosition position, game::Face face) override;

   std::optional<game::BlockStateId> on_neighbour_change(game::World &world,
                                                         game::BlockStateId block_state_id,
                                                         game::BlockStateId neighbour_block_state_id,
                                                         game::BlockPosition position,
                                                         game::Face face) override;

   bool on_player_action(game::World &world, game::PlayerId player_id, game::BlockStateId block_state_id,
                         game::BlockPosition position, game::Face face,
                         util::Vec3 crosshair_position) override;

 protected:
   enum class SourceBlockType
   {
      Air,
      Water
   };

   [[nodiscard]] static std::optional<SourceBlockType> get_source_block_type(game::World &world,
                                                                             game::BlockPosition pos);
   [[nodiscard]] static bool verify_source_block(game::World &world, game::BlockPosition pos);
   [[nodiscard]] static bool verify_source_is_air(game::World &world, game::BlockPosition pos);
   [[nodiscard]] static std::optional<game::Direction>
   find_player_direction(game::World &world, game::PlayerId player_id, game::BlockPosition position);
};

}// namespace minecpp::controller::block

#endif//MINECPP_DEFAULTCONTROLLER_H
