#pragma once

#include "Peer.h"

#include "minecpp/container/BasicBufferView.hpp"
#include "minecpp/signal/Delegate.hpp"

#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <string_view>

struct _ENetHost;
struct _ENetEvent;

namespace minecpp::stream {

class Peer;

class Host
{
   friend Peer;

 public:
   virtual ~Host();

   using ConnectionDelegate   = signal::Delegate<Peer *>;
   using ReceivedDelegate     = signal::Delegate<Peer *, container::BufferView>;
   using DisconnectedDelegate = signal::Delegate<Peer *, bool *>;
   ConnectionDelegate on_connected;
   ReceivedDelegate on_received;
   DisconnectedDelegate on_disconnected;

   void tick();

 protected:
   explicit Host(_ENetHost *host);

   [[nodiscard]] _ENetHost *host() const;

   std::unique_lock<std::mutex> lock();

   // be sure to use sync in a lock
   void flush();

   virtual std::shared_ptr<Peer> new_connection_to_shared_ptr(_ENetPeer *peer) = 0;
   void add_peer(std::size_t id, std::shared_ptr<Peer> peer);
   std::shared_ptr<Peer> peer_at(std::size_t id);
   bool host_service(_ENetEvent *event);

 private:
   _ENetHost *m_host;
   std::mutex m_mutex;
   std::unordered_map<std::size_t, std::shared_ptr<Peer>> m_peers;
};

}// namespace minecpp::stream