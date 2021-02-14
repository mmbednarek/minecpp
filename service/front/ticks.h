#pragma once
#include "server.h"
#include <minepb/chunk_storage.grpc.pb.h>

namespace Front {

typedef std::shared_ptr<minecpp::chunk_storage::ChunkStorage::Stub>
        ChunkService;

struct ChunkLoadTicket {
   bool loaded{false};
   minecpp::chunk::NetChunk chunk{};
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

}// namespace Front
