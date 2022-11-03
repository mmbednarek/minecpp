#pragma once
#include "../JobSystem.h"
#include <minecpp/game/Game.h>

namespace minecpp::service::engine {
class ChunkSystem;
}

namespace minecpp::service::engine::job {

class ChunkIsPresent : public IJobCondition
{
 public:
   ChunkIsPresent(ChunkSystem &chunk_system, const game::ChunkPosition &chunk_position);

   [[nodiscard]] JobConditionStatus status() const override;
   void resolve(JobSystem &job_system) override;

 private:
   ChunkSystem &m_chunk_system;
   game::ChunkPosition m_chunk_position;
};

}// namespace minecpp::service::engine::job
