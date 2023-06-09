#include "minecpp/container/BasicBuffer.hpp"
#include <minecpp/game/ChunkPosition.h>
#include <minecpp/service/storage/Storage.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::storage {

void StorageClient::subscribe_chunk(game::ChunkPosition position)
{
   proto::service::storage::v1::Request request;
   *request.mutable_chunk_subscription()->mutable_position() = position.to_proto();

   this->send(request);
}

void StorageClient::push_chunk(const world::Chunk *chunk)
{
   if (chunk == nullptr)
      return;

   proto::service::storage::v1::Request request;
   *request.mutable_chunk_data()->mutable_chunk_data() = chunk->to_proto();

   this->send(request);
}

Stream::Stream(stream::Client &client, const network::Endpoint &endpoint) :
    m_peer(client.create_peer(endpoint))
{
}

void Stream::send(const Request &req)
{
   container::Buffer buffer(static_cast<std::size_t>(req.ByteSizeLong()));
   req.SerializeToArray(buffer.data(), static_cast<int>(buffer.size()));
   m_peer->send_reliable_message(buffer.as_view());
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

bool StorageClient::send(const Request &request)
{
   m_streams.front().send(request);
   return false;
}

void StorageClient::tick()
{
   m_client.tick();
}

void StorageClient::on_connected(std::shared_ptr<stream::Peer> peer)
{
   spdlog::info("established connection to storage server at {}", peer->id());

   proto::service::storage::v1::Request request;
   request.mutable_set_client_id()->mutable_client_id()->set_value(m_client_id);

   container::Buffer buffer(static_cast<std::size_t>(request.ByteSizeLong()));
   request.SerializeToArray(buffer.data(), static_cast<int>(buffer.size()));
   peer->send_reliable_message(buffer.as_view());
}

void StorageClient::on_received_message(std::shared_ptr<stream::Peer> /*peer*/,
                                        minecpp::container::BufferView message)
{
   proto::service::storage::v1::Response response;
   response.ParseFromArray(message.data(), static_cast<int>(message.size()));

   m_handler.handle_response(std::move(response));
}

void StorageClient::on_disconnected(std::shared_ptr<stream::Peer> peer, bool *try_reconnect)
{
   spdlog::info("lost connection to server {}", peer->hostname());
   *try_reconnect = true;
}

}// namespace minecpp::service::storage