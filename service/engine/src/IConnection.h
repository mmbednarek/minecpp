#pragma once
#include <minecpp/game/Types.hpp>
#include <minecpp/proto/event/clientbound/v1/Clientbound.pb.h>
#include <span>

namespace minecpp::service::engine {

using ConnectionId = std::size_t;

class IConnection
{
 public:
   virtual ~IConnection() noexcept = default;

   virtual void send_to_player(const google::protobuf::Message &message, game::PlayerId player_id)        = 0;
   virtual void send_to_many(const google::protobuf::Message &message,
                             std::span<game::PlayerId> player_ids)                                        = 0;
   virtual void send_to_all_excluding(const google::protobuf::Message &message, game::PlayerId player_id) = 0;
   virtual void send_to_all(const google::protobuf::Message &message)                                     = 0;
};

}// namespace minecpp::service::engine