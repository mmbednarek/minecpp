#include "ChunkIsComplete.h"
#include "../ChunkSystem.h"

namespace minecpp::service::engine::job {

JobConditionStatus ChunkIsComplete::status() const
{
   switch (m_chunk_system.chunk_state_at(m_chunk_position)) {
   case world::ABSENT: return JobConditionStatus::NotQueued;
   case world::EMPTY: return JobConditionStatus::NotQueued;
   case world::TERRAIN: return JobConditionStatus::NotQueued;
   case world::COMPLETE: return JobConditionStatus::Complete;
   }

   return JobConditionStatus::NotQueued;
}

void ChunkIsComplete::resolve(JobSystem &job_system)
{
   m_chunk_system.subscribe_chunk(m_chunk_position);
}

ChunkIsComplete::ChunkIsComplete(ChunkSystem &chunk_system, const game::ChunkPosition &chunk_position) :
    m_chunk_system(chunk_system),
    m_chunk_position(chunk_position)
{
}

}// namespace minecpp::service::engine::job