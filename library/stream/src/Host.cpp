#include "Host.h"

#include "minecpp/container/BasicBuffer.hpp"

#include <enet/enet.h>
#include <spdlog/spdlog.h>

namespace minecpp::stream {

Host::Host(_ENetHost *host) :
    m_host{host}
{
}

Host::~Host()
{
   if (m_host != nullptr)
      enet_host_destroy(m_host);
   enet_deinitialize();
}

void Host::tick()
{
   ENetEvent event;
   while (this->host_service(&event)) {
      switch (event.type) {
      case ENET_EVENT_TYPE_CONNECT: {
         auto connection = this->new_connection_to_shared_ptr(event.peer);
         this->on_connected.publish(std::move(connection));
         break;
      }
      case ENET_EVENT_TYPE_DISCONNECT: {
         auto *peer         = static_cast<Peer *>(event.peer->data);
         bool try_reconnect = false;
         this->on_disconnected.publish(this->peer_at(peer->id()), &try_reconnect);

         if (try_reconnect) {
            peer->reconnect();
         } else {
            m_peers.erase(peer->id());
         }

         break;
      }
      case ENET_EVENT_TYPE_RECEIVE: {
         auto *peer = static_cast<Peer *>(event.peer->data);
         container::BufferView buffer(event.packet->data, event.packet->dataLength);
         this->on_received.publish(this->peer_at(peer->id()), buffer);
         break;
      }
      default: continue;
      }
   }
}

_ENetHost *Host::host() const
{
   return m_host;
}

void Host::add_peer(std::size_t id, std::shared_ptr<Peer> peer)
{
   m_peers.emplace(id, std::move(peer));
}

std::shared_ptr<Peer> Host::peer_at(std::size_t id)
{
   auto it = m_peers.find(id);
   if (it == m_peers.end())
      return {};
   return it->second;
}

void Host::flush()
{
   enet_host_flush(m_host);
}

std::unique_lock<std::mutex> Host::lock()
{
   return std::unique_lock{m_mutex};
}

bool Host::host_service(_ENetEvent *event)
{
   this->lock();
   return enet_host_service(m_host, event, 0) > 0;
}

}// namespace minecpp::stream
