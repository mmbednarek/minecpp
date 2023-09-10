#pragma once

#include "minecpp/container/BasicBufferView.hpp"
#include "minecpp/game/Types.hpp"

#include <span>

namespace minecpp::service::engine {

using ConnectionId = std::size_t;

class IConnection
{
 public:
   virtual ~IConnection() noexcept = default;

   virtual void send_to_many(container::BufferView message, std::span<game::PlayerId> player_ids) = 0;
   virtual void send_to_player(container::BufferView message, game::PlayerId player_id)           = 0;
   virtual void send_to_all(container::BufferView message)                                        = 0;
   virtual void send_to_all_excluding(container::BufferView message, game::PlayerId player_id)    = 0;
};

}// namespace minecpp::service::engine