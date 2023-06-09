#include "HandleStorageMessage.h"
#include "../ChunkSystem.h"

namespace minecpp::service::engine::job {

HandleStorageMessage::HandleStorageMessage(ChunkSystem &chunk_system, Response response) :
    m_chunk_system(chunk_system),
    m_response(std::move(response))
{
}

void HandleStorageMessage::run()
{
   switch (m_response.message_case()) {
   case Response::kChunkData: m_chunk_system.handle_chunk_data(m_response.chunk_data()); break;
   case Response::kEmptyChunk: m_chunk_system.handle_empty_chunk(m_response.empty_chunk()); break;
   default: break;
   }
}

}// namespace minecpp::service::engine::job
