#pragma once

#include "minecpp/container/BasicBufferView.hpp"

#include <memory>

struct _ENetPeer;

namespace minecpp::stream {

using Port = std::uint16_t;

class Host;
class Server;
class Client;

class Peer : public std::enable_shared_from_this<Peer>
{
   friend Server;
   friend Client;

 public:
   explicit Peer(Host &host, _ENetPeer *peer, bool is_client);

   void send_reliable_message(const container::BufferView &message);
   void send_unreliable_message(const container::BufferView &message);
   void disconnect();
   void reset();
   void reconnect();
   std::uint64_t id() const;
   std::string hostname();
   [[nodiscard]] bool is_connected() const;

 private:
   void set_is_connected(bool is_connected);

   Host &m_host;
   _ENetPeer *m_peer;
   std::uint32_t m_id;
   bool m_is_connected{false};
   bool m_is_client{false};
};

}// namespace minecpp::stream