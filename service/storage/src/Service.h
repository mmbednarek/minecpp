#pragma once

#include "IHandler.h"
#include "IResponder.h"
#include "IStorage.h"

#include "minecpp/net/storage/Serverbound.schema.h"

#include <map>

namespace minecpp::service::storage {

class Server;

using ClientId = std::uint64_t;

class Service : public IHandler
{
 public:
   explicit Service(Server &server, IStorage &storage);

   void handle_request(ConnectionId id, container::Buffer message) override;

   void on_set_client_id(ConnectionId connection_id, const net::storage::sb::SetClientId &message);
   void on_subscribe_chunk(ConnectionId connection_id, const net::storage::sb::SubscribeChunk &message);
   void on_store_chunk(ConnectionId connection_id, const net::storage::sb::StoreChunk &message);
   void on_failure(ConnectionId connection_id, std::uint8_t id);

 private:
   std::optional<ClientId> get_client_id(ConnectionId connection_id);

   Server &m_server;
   IStorage &m_storage;
   std::map<ConnectionId, ClientId> m_connection_to_client_map;
};

}// namespace minecpp::service::storage