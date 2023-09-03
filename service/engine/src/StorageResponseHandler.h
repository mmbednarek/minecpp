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
   void on_reply_empty_chunk(int a, const net::storage::cb::ReplyEmptyChunk &message) override;
   void on_reply_chunk(int a, const net::storage::cb::ReplyChunk &message) override;
   void on_failure(int a, std::uint8_t msg_code) override;

 private:
   ChunkSystem *m_chunk_system{};
   JobSystem &m_job_system;
};

}// namespace minecpp::service::engine
