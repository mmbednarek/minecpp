#include "minecpp/service/storage/Storage.h"
#include "minecpp/container/BasicBuffer.hpp"
#include "minecpp/game/ChunkPosition.h"
#include "minecpp/net/storage/Serverbound.schema.h"
#include "minecpp/util/Cast.hpp"
#include "minecpp/util/Context.h"
#include "minecpp/world/ChunkSerializer.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::storage {

void StorageClient::subscribe_chunk(game::ChunkPosition position)
{
   net::storage::sb::SubscribeChunk subscribe_chunk;
   subscribe_chunk.position = position.position();

   network::message::Writer writer;
   subscribe_chunk.serialize(writer);
   this->send(writer.buffer_view());
}

void StorageClient::push_chunk(world::Chunk *chunk)
{
   if (chunk == nullptr)
      return;

   net::storage::sb::StoreChunk store_chunk;
   world::ChunkSerializer serializer(*chunk);
   serializer.write_chunk(store_chunk.chunk);

   network::message::Writer writer;
   store_chunk.serialize(writer);
   this->send(writer.buffer_view());
}

Stream::Stream(stream::Client &client, const network::Endpoint &endpoint) :
    m_peer(client.create_peer(endpoint))
{
}

void Stream::send(const container::BufferView &message)
{
   m_peer->send_reliable_message(message);
}

bool Stream::is_connected() const
{
   return m_peer->is_connected();
}

StorageClient::StorageClient(ClientId client_id, IResponseHandler &handler) :
    m_client_id(client_id),
    m_handler(handler)
{
   m_client.on_connected.connect<&StorageClient::on_connected>(this);
   m_client.on_received.connect<&StorageClient::on_received_message>(this);
   m_client.on_disconnected.connect<&StorageClient::on_disconnected>(this);
}

void StorageClient::connect(const network::Endpoint &address)
{
   m_streams.emplace_back(m_client, address);
   this->tick();
}

bool StorageClient::send(const container::BufferView &request)
{
   assert(not m_streams.empty());
   m_streams.front().send(request);
   return false;
}

void StorageClient::tick()
{
   m_client.tick();
}

void StorageClient::on_connected(stream::Peer *peer)
{
   spdlog::info("established connection to storage server at {}", peer->id());

   net::storage::sb::SetClientId set_client_id;
   set_client_id.client_id = m_client_id;

   network::message::Writer writer;
   set_client_id.serialize(writer);
   this->send(writer.buffer_view());
}

void StorageClient::on_received_message(stream::Peer * /*peer*/, minecpp::container::BufferView message)
{
   auto stream = message.make_stream();
   network::message::Reader reader(stream);

   util::Context ctx;
   net::storage::cb::visit_message(m_handler, ctx, reader);
}

void StorageClient::on_disconnected(stream::Peer *peer, bool *try_reconnect)
{
   spdlog::info("lost connection to server {}", peer->hostname());
   *try_reconnect = true;
}

}// namespace minecpp::service::storage