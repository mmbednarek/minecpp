#pragma once

#include <minecpp/game/World.h>
#include <minecpp/world/IChunkSystem.h>

#include "../JobSystem.h"

namespace minecpp::service::engine::job {

class ChangeBlock :  public IJob {
 public:
   ChangeBlock(game::ILightSystem &light_system, world::IChunkSystem &chunk_system,
               const game::BlockPosition &position, game::BlockStateId target_state_id);

   void run() override;

 private:
   game::ILightSystem &m_light_system;
   world::IChunkSystem &m_chunk_system;

   game::BlockPosition m_position;
   game::BlockStateId m_target_state_id{};
};

}