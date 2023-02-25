#pragma once

#include <minecpp/game/IEntitySystem.hpp>
#include <minecpp/game/IWorld.h>
#include <minecpp/world/IChunkSystem.h>

#include "../JobSystem.h"

namespace minecpp::service::engine::job {

class ChangeBlock : public IJob
{
 public:
   ChangeBlock(game::IEntitySystem &entity_system, game::ILightSystem &light_system,
               world::IChunkSystem &chunk_system, const game::BlockPosition &position,
               game::BlockStateId target_state_id);

   void run() override;

 private:
   game::IEntitySystem &m_entity_system;
   game::ILightSystem &m_light_system;
   world::IChunkSystem &m_chunk_system;

   game::BlockPosition m_position;
   game::BlockStateId m_target_state_id{};
};

}// namespace minecpp::service::engine::job