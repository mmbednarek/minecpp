#pragma once

#include "IHandler.h"
#include "IResponder.h"
#include "IStorage.h"
#include <minecpp/game/Game.h>
#include <map>

namespace minecpp::service::storage {

using ClientId = std::uint64_t;

class Service : public IHandler
{
 public:
   explicit Service(IResponder &m_responder, IStorage &storage);

   void subscribe_chunk(ConnectionId connection_id, game::ChunkPosition position);
   void push_chunk_data(ConnectionId connection_id, const proto::chunk::v1::Chunk &position);
   void set_client_id(ConnectionId connection_id, ClientId client_id);

   void handle_request(ConnectionId id, const proto::service::storage::v1::Request &request) override;

 private:
   std::optional<ClientId> get_client_id(ConnectionId connection_id);

   IStorage &m_storage;
   IResponder &m_responder;
   std::map<ConnectionId, ClientId> m_connection_to_client_map;
};

}// namespace minecpp::service::storage