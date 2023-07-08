#pragma once

#include "minecpp/network/Network.h"
#include "minecpp/proto/chunk/Chunk.pb.h"
#include "minecpp/proto/service/storage/Storage.pb.h"
#include "minecpp/stream/Client.h"
#include "minecpp/world/Chunk.h"

#include <memory>
#include <shared_mutex>
#include <vector>

namespace minecpp::service::storage {

using proto::service::storage::Request;
using proto::service::storage::Response;

using proto::service::storage::ResponseChunkData;
using proto::service::storage::ResponseEmptyChunk;

using ClientId = std::uint64_t;

class IResponseHandler
{
 public:
   virtual ~IResponseHandler() noexcept = default;

   virtual void handle_response(Response response) = 0;
};

class Stream
{
 public:
   Stream(stream::Client &client, const network::Endpoint &endpoint);

   void send(const Request &req);
   [[nodiscard]] bool is_connected() const;

 private:
   std::shared_ptr<stream::Peer> m_peer;
};

class StorageClient
{
 public:
   explicit StorageClient(ClientId client_id, IResponseHandler &handler);

   StorageClient(const StorageClient &)                = delete;
   StorageClient &operator=(const StorageClient &)     = delete;
   StorageClient(StorageClient &&) noexcept            = delete;
   StorageClient &operator=(StorageClient &&) noexcept = delete;

   void connect(const network::Endpoint &address);
   bool send(const Request &request);
   void tick();

   void subscribe_chunk(game::ChunkPosition position);
   void push_chunk(const world::Chunk *chunk);

 private:
   void on_connected(std::shared_ptr<stream::Peer> peer);
   void on_received_message(std::shared_ptr<stream::Peer> peer, minecpp::container::BufferView message);
   void on_disconnected(std::shared_ptr<stream::Peer> peer, bool *try_reconnect);

   stream::Client m_client;
   ClientId m_client_id{};

   std::vector<Stream> m_streams;
   IResponseHandler &m_handler;

   std::mutex m_mutex;
};


}// namespace minecpp::service::storage