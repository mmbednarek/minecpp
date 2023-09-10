#include "ApiHandler.h"
#include "EventManager.h"
#include "job/HandlePlayerMessage.h"

#include "minecpp/container/BasicBuffer.hpp"
#include "minecpp/net/engine/Clientbound.schema.h"

#include <spdlog/spdlog.h>

using minecpp::proto::event::clientbound::Event;

namespace minecpp::service::engine {

Connection::Connection(std::shared_ptr<stream::Peer> peer) :
    m_peer{std::move(peer)}
{
}

void Connection::send_to_player(container::BufferView message, game::PlayerId player_id)
{
   net::engine::cb::SendMsgToSinglePlayer send_msg_to_single_player;
   send_msg_to_single_player.player_id = player_id;
   send_msg_to_single_player.data.resize(message.size());
   std::copy(message.begin(), message.end(), send_msg_to_single_player.data.begin());

   network::message::Writer writer;
   send_msg_to_single_player.serialize(writer);

   this->send(writer.buffer_view());
}

void Connection::send_to_all(container::BufferView message)
{
   net::engine::cb::SendMsgToAllPlayers send_msg_to_all_players;
   send_msg_to_all_players.data.resize(message.size());
   std::copy(message.begin(), message.end(), send_msg_to_all_players.data.begin());

   network::message::Writer writer;
   send_msg_to_all_players.serialize(writer);

   this->send(writer.buffer_view());
}

void Connection::send_to_all_excluding(container::BufferView message, game::PlayerId player_id)
{
   net::engine::cb::SendMsgToAllPlayersExcept send_msg_to_all_players_excluding;
   send_msg_to_all_players_excluding.data.resize(message.size());
   send_msg_to_all_players_excluding.player_id = player_id;
   std::copy(message.begin(), message.end(), send_msg_to_all_players_excluding.data.begin());

   network::message::Writer writer;
   send_msg_to_all_players_excluding.serialize(writer);

   this->send(writer.buffer_view());
}

void Connection::send_to_many(container::BufferView message, std::span<game::PlayerId> player_ids)
{
   net::engine::cb::SendMsgToSomePlayers send_msg_to_some_player;
   send_msg_to_some_player.player_ids.resize(player_ids.size());
   std::copy(player_ids.begin(), player_ids.end(), send_msg_to_some_player.player_ids.begin());
   send_msg_to_some_player.data.resize(message.size());
   std::copy(message.begin(), message.end(), send_msg_to_some_player.data.begin());

   network::message::Writer writer;
   send_msg_to_some_player.serialize(writer);

   this->send(writer.buffer_view());
}

void Connection::send(container::BufferView message)
{
   m_peer->send_reliable_message(message);
}

ApiHandler::ApiHandler(Service &service, EventManager &event_manager, JobSystem &job_system,
                       std::uint16_t port) :
    m_service{service},
    m_event_manager{event_manager},
    m_server{port},
    m_job_system{job_system}
{
   m_server.on_connected.connect<&ApiHandler::on_connected>(this);
   m_server.on_received.connect<&ApiHandler::on_received_message>(this);
   m_server.on_disconnected.connect<&ApiHandler::on_disconnected>(this);
}

void ApiHandler::on_connected(stream::Peer *peer)
{
   spdlog::info("received inbound connection from client id={}", peer->id());
   m_event_manager.add_client(peer->id(), std::make_unique<Connection>(peer->shared_from_this()));
}

void ApiHandler::on_received_message(stream::Peer * /*peer*/, container::BufferView message)
{
   m_job_system.create_job<job::HandlePlayerMessage>(m_service, container::Buffer(message));
}

void ApiHandler::on_disconnected(stream::Peer *peer, bool * /*try_reconnect*/)
{
   m_event_manager.remove_client(peer->id());
}

void ApiHandler::tick()
{
   m_server.tick();
}

}// namespace minecpp::service::engine