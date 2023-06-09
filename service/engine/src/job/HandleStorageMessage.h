#pragma once

#include "../JobSystem.h"

#include "minecpp/proto/service/storage/v1/Storage.pb.h"

namespace minecpp::service::engine {

class ChunkSystem;

}

namespace minecpp::service::engine::job {

class HandleStorageMessage : public IJob
{
 public:
   using Response = proto::service::storage::v1::Response;

   HandleStorageMessage(ChunkSystem &chunk_system, Response response);

   void run() override;

 private:
   ChunkSystem &m_chunk_system;
   Response m_response;
};

}// namespace minecpp::service::engine::job