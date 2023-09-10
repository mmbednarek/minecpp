#pragma once

#include "../JobSystem.h"

#include "minecpp/container/BasicBuffer.hpp"
#include "minecpp/net/engine/Serverbound.schema.h"

namespace minecpp::service::engine {
class Service;
}

namespace minecpp::service::engine::job {

class HandlePlayerMessage : public IJob
{
 public:
   HandlePlayerMessage(Service &service, container::Buffer event);

   void run() override;

   void on_accept_player(int stub, const net::engine::sb::AcceptPlayer &accept_player);
   void on_remove_player(int stub, const net::engine::sb::RemovePlayer &remove_player);
   void on_player_message(int stub, const net::engine::sb::PlayerMessage &player_message);
   void on_failure(int stub, std::uint8_t message_id);

 private:
   Service &m_service;
   container::Buffer m_event;
};

}// namespace minecpp::service::engine::job