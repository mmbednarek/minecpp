#pragma once

#include "IHandler.h"
#include "IResponder.h"

#include "minecpp/network/Network.h"
#include "minecpp/proto/service/storage/Storage.pb.h"
#include "minecpp/stream/Server.h"

namespace minecpp::service::storage {

namespace storage_v1 = minecpp::proto::service::storage;

class Connection
{
 public:
   explicit Connection(std::shared_ptr<stream::Peer> peer);

   void send(const storage_v1::Response &response);

 private:
   std::shared_ptr<stream::Peer> m_peer;
};

class Server : public IResponder
{
 public:
   explicit Server(network::Port port);

   Server(Server &)                      = delete;
   Server &operator=(Server &)           = delete;
   Server(Server &&) noexcept            = delete;
   Server &operator=(Server &&) noexcept = delete;

   void send(ConnectionId id, const storage_v1::Response &response) override;
   void set_handler(IHandler *handler);
   void tick();

 private:
   void on_connected(std::shared_ptr<stream::Peer> peer);
   void on_received_message(std::shared_ptr<stream::Peer> peer, container::BufferView message);
   void on_disconnected(std::shared_ptr<stream::Peer> peer, bool *try_reconnect);

   stream::Server m_server;
   std::mutex m_mutex;
   std::map<ConnectionId, std::unique_ptr<Connection>> m_connections;
   IHandler *m_handler{};
};

}// namespace minecpp::service::storage