#include "Server.h"

#include "minecpp/container/BasicBuffer.hpp"
#include "minecpp/stream/Server.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::storage {

Connection::Connection(std::shared_ptr<stream::Peer> peer) :
    m_peer(std::move(peer))
{
}

void Connection::send(const container::BufferView &response)
{
   m_peer->send_reliable_message(response);
}

Server::Server(network::Port port) :
    m_server(port)
{
   m_server.on_connected.connect<&Server::on_connected>(this);
   m_server.on_received.connect<&Server::on_received_message>(this);
   m_server.on_disconnected.connect<&Server::on_disconnected>(this);
}

void Server::send(ConnectionId id, const container::BufferView &response)
{
   auto it = m_connections.find(id);
   if (it == m_connections.end()) {
      spdlog::error("could not find connection {}", id);
      return;
   }
   it->second->send(response);
}

void Server::set_handler(IHandler *handler)
{
   m_handler = handler;
}

void Server::on_connected(stream::Peer *peer)
{
   auto id = peer->id();
   spdlog::info("received connection from peer: {}", id);

   std::unique_lock lock{m_mutex};
   m_connections.emplace(id, std::make_unique<Connection>(peer->shared_from_this()));
}

void Server::on_received_message(const stream::Peer *peer, container::BufferView message)
{
   assert(m_handler);

   m_handler->handle_request(peer->id(), container::Buffer(message));
}

void Server::on_disconnected(const stream::Peer *peer, bool * /*try_reconnect*/)
{
   spdlog::info("received connection from peer: {}", peer->id());
   m_connections.erase(peer->id());
}

void Server::tick()
{
   m_server.tick();
}

}// namespace minecpp::service::storage
