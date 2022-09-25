#include "Service.h"
#include <spdlog/spdlog.h>

namespace minecpp::service::storage {

Service::Service(IResponder &responder, IStorage &storage) :
    m_storage(storage),
    m_responder(responder)
{
}

void Service::subscribe_chunk(ConnectionId connection_id, game::ChunkPosition position)
{
   spdlog::info("handling subscribe chunk {} {}", position.x, position.z);

   auto client_id = this->get_client_id(connection_id);
   if (not client_id.has_value()) {
      spdlog::error("client tries to subscribe to a chunk without provided client id");
      return;
   }

   proto_storage::ClientId proto_client_id;
   proto_client_id.set_value(*client_id);

   m_storage.add_chunk_subscription(position, proto_client_id);

   auto chunk = m_storage.read_chunk(position);
   if (not chunk.has_value()) {
      spdlog::error("could not read chunk at: {} {}", position.x, position.z);
      return;
   }

   proto::service::storage::v1::Response response;
   *response.mutable_chunk_data()->mutable_chunk_data() = *chunk;
   m_responder.send(connection_id, response);
}

void Service::handle_request(ConnectionId connection_id, const proto::service::storage::v1::Request &request)
{
   using proto::service::storage::v1::Request;

   switch (request.message_case()) {
   case Request::kChunkSubscription:
      this->subscribe_chunk(connection_id, game::ChunkPosition::from_proto(request.chunk_subscription().position()));
      break;
   case Request::kChunkData:
      this->push_chunk_data(connection_id, request.chunk_data().chunk_data());
      break;
   case Request::kSetClientId:
      this->set_client_id(connection_id, request.set_client_id().client_id().value());
      return;
   default:
      spdlog::warn("unhandled message case: {}", request.message_case());
      break;
   }
}

void Service::push_chunk_data(ConnectionId /* connection_id */, const proto::chunk::v1::Chunk &chunk)
{
   m_storage.update_chunk(game::ChunkPosition::from_proto(chunk.position()), [&chunk](proto_chunk::Chunk &db_chunk) {
      db_chunk = chunk;
   });
}

void Service::set_client_id(ConnectionId connection, ClientId client_id) {
   m_connection_to_client_map[connection] = client_id;
}

std::optional<ClientId> Service::get_client_id(ConnectionId connection_id)
{
   auto pair = m_connection_to_client_map.find(connection_id);
   if (pair == m_connection_to_client_map.end())
      return std::nullopt;

   return pair->second;
}

}// namespace minecpp::service::storage
