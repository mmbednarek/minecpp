#pragma once
#include "ApiHandler.h"
#include "IConnection.h"
#include <minecpp/game/player/Id.h>
#include <minecpp/proto/event/clientbound/v1/Clientbound.pb.h>
#include <minecpp/util/StaticQueue.h>
#include <queue>
#include <span>
#include <spdlog/spdlog.h>
#include <string>

namespace minecpp::service::engine {

class EventHandler;

class EventManager
{
 public:
   using Message = google::protobuf::Message;

   void send_to(const Message &message, game::PlayerId player_id);
   void send_to_many(const Message &message, std::span<game::PlayerId> player_id);
   void send_to_all(const Message &message);
   void send_to_all_excluding(const Message &message, game::PlayerId player_id);

   [[nodiscard]] IConnection *client(ConnectionId id);
   void add_client(std::unique_ptr<IConnection> stream);

 private:
   ConnectionId m_top_connection_id{};
   std::map<ConnectionId, std::unique_ptr<IConnection>> m_queues;
   std::mutex m_queue_mutex;
};

}// namespace minecpp::service::engine
