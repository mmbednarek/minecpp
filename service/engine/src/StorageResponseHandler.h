#pragma once
#include <minecpp/service/storage/Storage.h>

namespace minecpp::service::engine {

class StorageResponseHandler : public storage::IResponseHandler
{
 public:
   void handle_chunk_data(const storage::ResponseChunkData &chunk) override;

   void add_handler(storage::IResponseHandler *handler);

 private:
   std::vector<storage::IResponseHandler *> m_handlers;
};

}
