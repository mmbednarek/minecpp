#include "Api.h"

#include "minecpp/container/BasicBuffer.hpp"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

ClientStream::ClientStream(stream::Client &client, const network::Endpoint &endpoint) :
    m_peer(client.create_peer(endpoint))
{
}

void ClientStream::send(container::BufferView message)
{
   assert(m_peer);
   m_peer->send_reliable_message(message);
}

void Client::on_connected(stream::Peer *peer)
{
   spdlog::info("established connection to server {}", peer->hostname());
}

void Client::on_received_message(stream::Peer * /*peer*/, container::BufferView message)
{
   auto stream = message.make_stream();
   network::message::Reader reader(stream);
   net::engine::cb::visit_message(m_visitor, *this, reader);
}

void Client::on_disconnected(stream::Peer *peer, bool *try_reconnect)
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

bool Client::send(container::BufferView message)
{
   assert(not m_streams.empty());

   int limit = static_cast<int>(m_streams.size());
   while (limit != 0 && not m_streams[m_round].is_connected()) {
      m_round = (m_round + 1) % m_streams.size();
      --limit;
   }
   if (limit == 0)
      return false;

   m_streams[m_round].send(message);
   m_round = (m_round + 1) % m_streams.size();

   return true;
}

void Client::tick()
{
   m_client.tick();
}

}// namespace minecpp::service::engine