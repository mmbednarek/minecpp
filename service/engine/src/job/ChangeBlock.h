#pragma once

#include <minecpp/game/IWorld.hpp>
#include <minecpp/world/IChunkSystem.h>

#include "../JobSystem.h"

namespace minecpp::service::engine::job {

class ChangeBlock : public IJob
{
 public:
   ChangeBlock(game::IWorld &world, world::IChunkSystem &chunk_system, const game::BlockPosition &position,
               game::BlockStateId target_state_id);

   void run() override;

 private:
   game::IWorld &m_world;
   world::IChunkSystem &m_chunk_system;

   game::BlockPosition m_position;
   game::BlockStateId m_target_state_id{};
};

}// namespace minecpp::service::engine::job