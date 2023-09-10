#include "EventHandler.h"

#include "minecpp/game/player/Player.h"
#include "minecpp/service/engine/Api.h"
#include "minecpp/world/Section.h"

#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h>

namespace minecpp::service::front {

void RawMsg::serialize(network::message::Writer &writer) const
{
   writer.write_bytes(reinterpret_cast<const char *>(message.data()), message.size());
}

EventHandler::EventHandler(Server &server) :
    m_server(server)
{
}

void EventHandler::set_client(engine::Client *client)
{
   m_client = client;
}

void EventHandler::on_send_msg_to_single_player(engine::Client &client,
                                                const net::engine::cb::SendMsgToSinglePlayer &msg)
{
   auto conn = m_server.connection_by_player_id(msg.player_id);
   if (not conn) {
      spdlog::error("connection {} is null", game::player::format_player_id(msg.player_id));
      return;
   }

   conn->send_message(RawMsg{
           container::BufferView{const_cast<std::uint8_t *>(msg.data.data()), msg.data.size()}
   });
}

void EventHandler::on_send_msg_to_some_players(engine::Client &client,
                                               const net::engine::cb::SendMsgToSomePlayers &msg)
{
   for (auto player_id : msg.player_ids) {
      auto conn = m_server.connection_by_player_id(player_id);
      if (not conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         continue;
      }

      conn->send_message(RawMsg{
              container::BufferView{const_cast<std::uint8_t *>(msg.data.data()), msg.data.size()}
      });
   }
}

void EventHandler::on_send_msg_to_all_players(engine::Client &client,
                                              const net::engine::cb::SendMsgToAllPlayers &msg)
{
   for (auto &[_, conn] : m_server) {
      if (conn.get() == nullptr)
         continue;

      conn->send_message(RawMsg{
              container::BufferView{const_cast<std::uint8_t *>(msg.data.data()), msg.data.size()}
      });
   }
}

void EventHandler::on_send_msg_to_all_players_except(engine::Client &client,
                                                     const net::engine::cb::SendMsgToAllPlayersExcept &msg)
{
   for (auto &[_, conn] : m_server) {
      if (conn.get() == nullptr)
         continue;
      if (conn->uuid() == msg.player_id)
         continue;

      conn->send_message(RawMsg{
              container::BufferView{const_cast<std::uint8_t *>(msg.data.data()), msg.data.size()}
      });
   }
}

void EventHandler::on_failure(engine::Client &client, std::uint8_t message_id)
{
   spdlog::warn("event-handler: couldn't parse engine message, ID={}", message_id);
}

}// namespace minecpp::service::front
