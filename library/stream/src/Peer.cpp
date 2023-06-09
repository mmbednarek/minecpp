#include "Peer.h"
#include "Host.h"

#include "minecpp/container/BasicBuffer.hpp"

#include <cstring>
#include <enet/enet.h>
#include <spdlog/spdlog.h>

namespace minecpp::stream {

Peer::Peer(Host &host, ENetPeer *peer, bool is_client) :
    m_host(host),
    m_peer(peer),
    m_id(static_cast<std::uint32_t>(peer->connectID)),
    m_is_client{is_client}
{
   m_peer->data = this;
}

void Peer::send_reliable_message(const container::BufferView &message)
{
  ENetPacket *packet = enet_packet_create(message.data(), message.size(), ENET_PACKET_FLAG_RELIABLE);

   auto lk = m_host.lock();
   enet_peer_send(m_peer, 0, packet);
}

void Peer::send_unreliable_message(const container::BufferView &message)
{
   ENetPacket *packet = enet_packet_create(message.data(), message.size(), 0);

   auto lk = m_host.lock();
   enet_peer_send(m_peer, 0, packet);
}

std::string Peer::hostname()
{
   container::BasicBuffer<char> buffer(128);
   if (enet_address_get_host(&m_peer->address, buffer.data(), buffer.size()) != 0)
      return {};
   buffer.truncate(std::strlen(buffer.data()) + 1);
   return buffer.to_string();
}

void Peer::disconnect()
{
   enet_peer_disconnect(m_peer, 0);
}

void Peer::reset()
{
   enet_peer_reset(m_peer);
}

std::uint64_t Peer::id() const
{
   return m_id;
}

void Peer::reconnect()
{
   if (not m_is_client)
      return;

   spdlog::info("stream: reconnecting host");
   m_peer       = enet_host_connect(m_peer->host, &m_peer->address, 2, 0);
   m_peer->data = this;
}

bool Peer::is_connected() const
{
   return m_is_connected;
}

void Peer::set_is_connected(const bool is_connected)
{
   m_is_connected = is_connected;
}

}// namespace minecpp::stream