#pragma once

#include <minecpp/service/storage/Storage.h>

namespace minecpp::service::engine {

class ChunkSystem;
class JobSystem;

class StorageResponseHandler : public storage::IResponseHandler
{
 public:
   explicit StorageResponseHandler(JobSystem &job_system);

   void set_chunk_system(ChunkSystem *chunk_system);
   void handle_response(storage::Response response) override;

 private:
   ChunkSystem *m_chunk_system{};
   JobSystem &m_job_system;
};

}// namespace minecpp::service::engine
