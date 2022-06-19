#pragma once
#include "block/Default.h"
#include "BlockController.hpp"
#include <map>
#include <memory>
#include <minecpp/game/Game.h>
#include <minecpp/game/World.h>

namespace minecpp::controller {

class BlockManager : public BlockController
{
   std::map<game::BlockId, std::unique_ptr<BlockController>> m_controllers;
   block::Default m_default_controller;

 public:
   bool on_player_place_block(game::World &world, game::PlayerId player_id, game::BlockId block_id,
                              game::BlockPosition position, game::Face face) override;

   std::optional<game::BlockStateId> on_neighbour_change(game::World &world,
                                                         game::BlockStateId block_state_id,
                                                         game::BlockStateId neighbour_block_state_id,
                                                         game::BlockPosition position, game::Face face) override;

   bool on_player_action(game::World &world, game::PlayerId player_id, game::BlockStateId block_state_id,
                         game::BlockPosition position, game::Face face,
                         util::Vec3 crosshair_position) override;

   BlockController &controller(game::BlockId block_id);

   template<typename TController, typename... TArgs>
   void register_controller(game::BlockId block_id, TArgs &&...args)
   {
      m_controllers[block_id] = std::make_unique<TController>(std::forward<TArgs>(args)...);
   }
};

}// namespace minecpp::controller
