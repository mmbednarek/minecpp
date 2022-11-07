#pragma once
#include "../JobSystem.h"
#include <minecpp/game/Game.h>
#include <minecpp/world/Generator.h>

namespace minecpp::service::engine::job {

class GenerateChunk : public IJob
{
 public:
   GenerateChunk(world::Generator &generator, const game::ChunkPosition &position);

   void run() override;

 private:
   world::Generator &m_generator;
   game::ChunkPosition m_position;
};

}// namespace minecpp::service::engine::job