#pragma once
#include <minecpp/game/Game.h>
#include <minecpp/proto/event/clientbound/v1/Clientbound.pb.h>

namespace minecpp::service::engine {

using ConnectionId = std::size_t;

class IConnection
{
 public:
   virtual ~IConnection() noexcept = default;

   virtual void send_to_player(const google::protobuf::Message &message, game::PlayerId player_id) = 0;
   virtual void send_to_all(const google::protobuf::Message &message) = 0;
};

}// namespace minecpp::service::engine