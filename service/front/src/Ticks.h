#pragma once
#include "Server.h"
#include <minecpp/proto/service/chunk_storage/v1/ChunkStorage.grpc.pb.h>

namespace minecpp::service::front {

class TickManager
{
   Server &server;

 public:
   explicit TickManager(Server &server);

   [[noreturn]] void tick();
   void keep_alive();
};

}// namespace minecpp::service::front
