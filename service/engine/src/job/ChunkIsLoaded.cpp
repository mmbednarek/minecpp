#include "../ChunkSystem.h"
#include "ChunkIsPresent.h"

namespace minecpp::service::engine::job {

JobConditionStatus ChunkIsPresent::status() const
{
   switch (m_chunk_system.chunk_state(m_chunk_position)) {
   case SubscriptionState::Unsubscribed: return JobConditionStatus::NotQueued;
   case SubscriptionState::SubscriptionIssued: return JobConditionStatus::Queued;
   case SubscriptionState::Subscribed: return JobConditionStatus::Complete;
   }

   return JobConditionStatus::NotQueued;
}

void ChunkIsPresent::resolve(JobSystem &job_system)
{
   m_chunk_system.subscribe_chunk(m_chunk_position);
}

ChunkIsPresent::ChunkIsPresent(ChunkSystem &chunk_system, const game::ChunkPosition &chunk_position) :
    m_chunk_system(chunk_system),
    m_chunk_position(chunk_position)
{
}

}// namespace minecpp::service::engine::job