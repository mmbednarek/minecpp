#pragma once
#include "block/Default.h"
#include <map>
#include <memory>
#include <minecpp/game/IBlockController.hpp>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::controller {

class BlockManager : public game::IBlockController
{
   std::map<game::BlockId, std::unique_ptr<IBlockController>> m_controllers;
   block::Default m_default_controller;

 public:
   bool on_player_place_block(game::IWorld &world, game::PlayerId player_id, int block_id,
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

   IBlockController &controller(game::BlockId block_id);

   template<typename TController, typename... TArgs>
   void register_controller(game::BlockId block_id, TArgs &&...args)
   {
      m_controllers[block_id] = std::make_unique<TController>(std::forward<TArgs>(args)...);
   }
};

}// namespace minecpp::controller
