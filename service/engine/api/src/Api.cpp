#include "Api.h"

#include "minecpp/container/BasicBuffer.hpp"
#include "minecpp/proto/event/clientbound/Clientbound.pb.h"
#include "minecpp/proto/event/serverbound/Serverbound.pb.h"

#include <charconv>
#include <spdlog/spdlog.h>

namespace pb = google::protobuf;

namespace minecpp::service::engine {

ClientStream::ClientStream(stream::Client &client, const network::Endpoint &endpoint) :
    m_peer(client.create_peer(endpoint))
{
}

void ClientStream::send(const pb::Message &message, game::PlayerId id)
{
   assert(m_peer);

   proto::event::serverbound::Event proto_event;
   proto_event.mutable_payload()->PackFrom(message);
   *proto_event.mutable_player_id() = game::player::write_id_to_proto(id);

   container::Buffer buffer(static_cast<std::size_t>(proto_event.ByteSizeLong()));
   proto_event.SerializeToArray(buffer.data(), static_cast<int>(buffer.size()));
   m_peer->send_reliable_message(buffer.as_view());
}

void Client::on_connected(std::shared_ptr<stream::Peer> peer)
{
   spdlog::info("established connection to server {}", peer->hostname());
}

void Client::on_received_message(std::shared_ptr<stream::Peer> /*peer*/, container::BufferView message)
{
   proto::event::clientbound::Event proto_event;
   proto_event.ParseFromArray(message.data(), static_cast<int>(message.size()));
   m_visitor.visit_event(proto_event);
}

void Client::on_disconnected(std::shared_ptr<stream::Peer> peer, bool *try_reconnect)
{
   spdlog::info("lost connection to server {}", peer->hostname());
   *try_reconnect = true;
}

bool ClientStream::is_connected() const
{
   return m_peer->is_connected();
}

Client::Client(IVisitor &visitor) :
    m_visitor{visitor}
{
   m_client.on_connected.connect<&Client::on_connected>(this);
   m_client.on_received.connect<&Client::on_received_message>(this);
   m_client.on_disconnected.connect<&Client::on_disconnected>(this);
}

void Client::connect(const network::Endpoint &address)
{
   m_streams.emplace_back(m_client, address);
   this->tick();
}

bool Client::send(const pb::Message &message, game::PlayerId id)
{
   assert(not m_streams.empty());

   int limit = static_cast<int>(m_streams.size());
   while (limit != 0 && not m_streams[m_round].is_connected()) {
      m_round = (m_round + 1) % m_streams.size();
      --limit;
   }
   if (limit == 0)
      return false;

   m_streams[m_round].send(message, id);
   m_round = (m_round + 1) % m_streams.size();

   return true;
}

void Client::tick()
{
   m_client.tick();
}

}// namespace minecpp::service::engine