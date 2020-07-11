#pragma once
#include "server.h"
#include <minepb/chunk_storage.grpc.pb.h>

namespace Front {

typedef std::shared_ptr<minecpp::chunk_storage::ChunkStorage::Stub>
    ChunkService;

class TickManager {
   Server &server;
   const ChunkService &chunk_service;

 public:
   TickManager(Server &server, const ChunkService &chunks);

   [[noreturn]] void tick();
   void keep_alive();
   void load_chunks();
};

}
