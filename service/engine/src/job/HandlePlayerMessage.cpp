#include "HandlePlayerMessage.h"

#include "../Service.h"


#include <spdlog/spdlog.h>

namespace minecpp::service::engine::job {

HandlePlayerMessage::HandlePlayerMessage(Service &service, container::Buffer event) :
    m_service{service},
    m_event{std::move(event)}
{
}

void HandlePlayerMessage::run()
{
   auto stream = m_event.make_stream();
   network::message::Reader reader(stream);

   int stub{};
   net::engine::sb::visit_message(*this, stub, reader);
}

void HandlePlayerMessage::on_accept_player(int stub, const net::engine::sb::AcceptPlayer &accept_player)
{
   m_service.on_accept_player(accept_player.player_id, accept_player.name);
}

void HandlePlayerMessage::on_remove_player(int stub, const net::engine::sb::RemovePlayer &remove_player)
{
   m_service.on_remove_player(remove_player.player_id);
}

void HandlePlayerMessage::on_player_message(int stub, const net::engine::sb::PlayerMessage &player_message)
{
   m_service.handle_raw_message(player_message.player_id,
                                container::BufferView(const_cast<std::uint8_t *>(player_message.data.data()),
                                                      player_message.data.size()));
}

void HandlePlayerMessage::on_failure(int stub, std::uint8_t message_id)
{
   spdlog::warn("handler-player-message: failed to parse message with id {}", message_id);
}

}// namespace minecpp::service::engine::job
