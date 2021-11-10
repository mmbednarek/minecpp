#pragma once
#include "server.h"
#include <minecpp/proto/service/chunk_storage/v1/chunk_storage.grpc.pb.h>

namespace minecpp::service::front {

typedef std::shared_ptr<minecpp::proto::service::chunk_storage::v1::ChunkStorage::Stub>
        ChunkService;

struct ChunkLoadTicket {
   bool loaded{false};
   minecpp::proto::chunk::v1::Chunk chunk{};
   std::shared_ptr<Connection> conn;
};

class TickManager {
   Server &server;
   const ChunkService &chunk_service;
   std::vector<std::future<ChunkLoadTicket>> m_future_chunks;

 public:
   TickManager(Server &server, const ChunkService &chunks);

   [[noreturn]] void tick();
   void keep_alive();
   void load_chunks();
};

}// namespace minecpp::service::front
