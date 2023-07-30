#include "ApiHandler.h"
#include "EventManager.h"
#include "job/HandlePlayerMessage.h"

#include "minecpp/container/BasicBuffer.hpp"
#include "minecpp/event/Serverbound.h"

#include <spdlog/spdlog.h>

using minecpp::proto::event::clientbound::Event;

namespace minecpp::service::engine {

Connection::Connection(std::shared_ptr<stream::Peer> peer) :
    m_peer{std::move(peer)}
{
}

void Connection::send_to_player(const google::protobuf::Message &message, game::PlayerId player_id)
{
   Event proto_event;
   *proto_event.mutable_single_player()->mutable_player_id() = game::player::write_id_to_proto(player_id);
   proto_event.mutable_payload()->PackFrom(message);
   this->send(proto_event);
}

void Connection::send_to_all(const google::protobuf::Message &message)
{
   Event proto_event;
   *proto_event.mutable_all_players() = proto::event::clientbound::RecipientAllPlayers();
   proto_event.mutable_payload()->PackFrom(message);
   this->send(proto_event);
}

void Connection::send_to_all_excluding(const google::protobuf::Message &message, game::PlayerId player_id)
{
   Event proto_event;
   *proto_event.mutable_excluding()->mutable_player_id() = game::player::write_id_to_proto(player_id);
   proto_event.mutable_payload()->PackFrom(message);
   this->send(proto_event);
}

void Connection::send_to_many(const google::protobuf::Message &message, std::span<game::PlayerId> player_ids)
{
   Event proto_event;
   for (auto player_id : player_ids) {
      auto [lower, upper] = util::write_uuid(player_id);
      auto *proto_id      = proto_event.mutable_multiple_players()->add_player_ids();
      proto_id->set_lower(lower);
      proto_id->set_upper(upper);
   }
   proto_event.mutable_payload()->PackFrom(message);
   this->send(proto_event);
}

void Connection::send(const Event &event)
{
   container::Buffer buffer(static_cast<std::size_t>(event.ByteSizeLong()));
   event.SerializeToArray(buffer.data(), static_cast<int>(buffer.size()));
   m_peer->send_reliable_message(buffer.as_view());
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

void ApiHandler::on_connected(std::shared_ptr<stream::Peer> peer)
{
   spdlog::info("received inbound connection from client id={}", peer->id());
   m_event_manager.add_client(peer->id(), std::make_unique<Connection>(std::move(peer)));
}

void ApiHandler::on_received_message(std::shared_ptr<stream::Peer> /*peer*/, container::BufferView message)
{
   proto::event::serverbound::Event proto_event;
   proto_event.ParseFromArray(message.data(), static_cast<int>(message.size()));

   m_job_system.create_job<job::HandlePlayerMessage>(m_service, std::move(proto_event));
}

void ApiHandler::on_disconnected(std::shared_ptr<stream::Peer> peer, bool * /*try_reconnect*/)
{
   m_event_manager.remove_client(peer->id());
}

void ApiHandler::tick()
{
   m_server.tick();
}

}// namespace minecpp::service::engine