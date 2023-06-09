#pragma once
#include "Server.h"

#include "minecpp/service/engine/Api.h"

namespace minecpp::service::front {

class TickManager
{
 public:
   explicit TickManager(Server &server, engine::Client &client);

   [[noreturn]] void tick();
   void keep_alive();

 private:
   Server &m_server;
   engine::Client &m_client;
};

}// namespace minecpp::service::front
