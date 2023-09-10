#pragma once

#include "minecpp/net/storage/Clientbound.schema.h"
#include "minecpp/network/Network.h"
#include "minecpp/stream/Client.h"
#include "minecpp/world/Chunk.h"

#include <memory>
#include <shared_mutex>
#include <vector>

namespace minecpp::service::storage {

using ClientId = std::uint64_t;

class IResponseHandler
{
 public:
   virtual ~IResponseHandler() noexcept = default;

   virtual void on_reply_empty_chunk(int a, const net::storage::cb::ReplyEmptyChunk &message) = 0;
   virtual void on_reply_chunk(int a, const net::storage::cb::ReplyChunk &message)            = 0;
   virtual void on_failure(int a, std::uint8_t msg_code)                                      = 0;
};

class Stream
{
 public:
   Stream(stream::Client &client, const network::Endpoint &endpoint);

   void send(const container::BufferView &message);
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
   bool send(const container::BufferView &request);
   void tick();

   void subscribe_chunk(game::ChunkPosition position);
   void push_chunk(world::Chunk *chunk);

 private:
   void on_connected(stream::Peer *peer);
   void on_received_message(stream::Peer *peer, minecpp::container::BufferView message);
   void on_disconnected(stream::Peer *peer, bool *try_reconnect);

   stream::Client m_client;
   ClientId m_client_id{};

   std::vector<Stream> m_streams;
   IResponseHandler &m_handler;

   std::mutex m_mutex;
};


}// namespace minecpp::service::storage