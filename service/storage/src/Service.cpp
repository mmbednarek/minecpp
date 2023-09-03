#include "Service.h"

#include "Server.h"

#include "minecpp/net/storage/Clientbound.schema.h"
#include "minecpp/util/Cast.hpp"

#include <spdlog/spdlog.h>

namespace minecpp::service::storage {

Service::Service(Server &server, IStorage &storage) :
    m_server(server),
    m_storage(storage)
{
}

std::optional<ClientId> Service::get_client_id(ConnectionId connection_id)
{
   auto pair = m_connection_to_client_map.find(connection_id);
   if (pair == m_connection_to_client_map.end())
      return std::nullopt;

   return pair->second;
}

void Service::handle_request(ConnectionId id, container::Buffer message)
{
   auto stream = message.make_stream();
   network::message::Reader reader(stream);

   net::storage::sb::visit_message(*this, id, reader);
}

void Service::on_set_client_id(ConnectionId connection_id, const net::storage::sb::SetClientId &message)
{
   m_connection_to_client_map[connection_id] = message.client_id;
}

void Service::on_subscribe_chunk(ConnectionId connection_id, const net::storage::sb::SubscribeChunk &message)
{
   auto x = message.position.x();
   auto y = message.position.y();
   spdlog::info("service: processing chunk subscription {} {}", x, y);

   auto client_id = this->get_client_id(connection_id);
   if (not client_id.has_value()) {
      spdlog::error("client tries to subscribe to a chunk without provided client id");
      return;
   }

   game::ChunkPosition chunk_position{message.position};

   m_storage.add_chunk_subscription(chunk_position, *client_id);

   auto chunk = m_storage.read_chunk(chunk_position);
   if (not chunk.has_value()) {
      spdlog::info("no chunk found at {} {}", chunk_position.x(), chunk_position.z());

      net::storage::cb::ReplyEmptyChunk reply;
      reply.position = message.position;

      network::message::Writer writer;
      reply.serialize(writer);

      container::BufferView buffer(util::unsafe_cast<unsigned char*>(writer.view().data()), writer.view().size());
      m_server.send(connection_id, buffer);
      return;
   }

   net::storage::cb::ReplyChunk reply;
   reply.chunk = std::move(*chunk);

   network::message::Writer writer;
   reply.serialize(writer);

   container::BufferView buffer(util::unsafe_cast<unsigned char*>(writer.view().data()), writer.view().size());
   m_server.send(connection_id, buffer);

   spdlog::info("sending chunk {} {} to client", message.position.x(), message.position.y());
}

void Service::on_store_chunk(ConnectionId /*connection_id*/, const net::storage::sb::StoreChunk &message)
{
   spdlog::info("storing chunk data at {}, {}", message.chunk.position.x(), message.chunk.position.y());

   if (not m_storage.update_chunk(game::ChunkPosition(message.chunk.position),
                                  [&message](net::Chunk &db_chunk) { db_chunk = message.chunk; })) {
      spdlog::warn("failed to store chunk at {}, {}", message.chunk.position.x(), message.chunk.position.y());
   }
}

void Service::on_failure(ConnectionId connection_id, std::uint8_t id) {
   spdlog::warn("failed to parse message from client {}, message id {}", connection_id, id);
}

}// namespace minecpp::service::storage
