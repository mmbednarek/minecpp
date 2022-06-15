#include "block/Default.h"
#include "BlockController.hpp"
#include <map>
#include <memory>
#include <minecpp/game/World.h>
#include <minecpp/player/Id.h>

namespace minecpp::game::controller {

class BlockManager
{
   std::map<int, std::unique_ptr<BlockController>> m_controllers;
   block::Default m_default_controller;

 public:
   bool on_player_place_block(World &world, player::Id player_id, int block_id, BlockPosition position,
                              Face face);

   BlockController &controller(int block_id);

   template<typename TController, typename... TArgs>
   void register_controller(int block_id, TArgs &&...args)
   {
      m_controllers[block_id] = std::make_unique<TController>(std::forward<TArgs>(args)...);
   }
};

}// namespace minecpp::game::controller
