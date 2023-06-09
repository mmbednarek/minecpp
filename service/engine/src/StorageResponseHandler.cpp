#include "StorageResponseHandler.h"
#include "ChunkSystem.h"
#include "job/HandleStorageMessage.h"
#include "JobSystem.h"

namespace minecpp::service::engine {

StorageResponseHandler::StorageResponseHandler(JobSystem &job_system) :
    m_job_system(job_system)
{
}

void StorageResponseHandler::set_chunk_system(ChunkSystem *chunk_system)
{
   m_chunk_system = chunk_system;
}

void StorageResponseHandler::handle_response(storage::Response response)
{
   assert(m_chunk_system);
   m_job_system.create_job<job::HandleStorageMessage>(*m_chunk_system, std::move(response));
}

}// namespace minecpp::service::engine
