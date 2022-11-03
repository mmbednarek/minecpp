#include "StorageResponseHandler.h"

namespace minecpp::service::engine {

void StorageResponseHandler::handle_chunk_data(const storage::ResponseChunkData &chunk)
{
   for (auto *handler : m_handlers) {
      if (handler == nullptr)
         continue;

      handler->handle_chunk_data(chunk);
   }
}

void StorageResponseHandler::add_handler(storage::IResponseHandler *handler) {
   m_handlers.emplace_back(handler);
}

}// namespace minecpp::service::engine
