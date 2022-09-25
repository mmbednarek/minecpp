#include <memory>
#include <minecpp/game/Game.h>
#include <minecpp/grpc/client/Bidi.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <minecpp/proto/service/storage/v1/Storage.grpc.pb.h>
#include <minecpp/world/Chunk.h>
#include <shared_mutex>
#include <vector>

namespace minecpp::service::storage {

using proto::service::storage::v1::Request;
using proto::service::storage::v1::Response;
using proto::service::storage::v1::StorageService;

using proto::service::storage::v1::ResponseChunkData;

using ConnectionManager = grpc::client::ConnectionManager<StorageService::Stub, Request, Response>;
using RawStream         = grpc::client::Stream<ConnectionManager>;
using ClientId          = std::uint64_t;

class IResponseHandler
{
 public:
   virtual ~IResponseHandler() noexcept = default;

   virtual void handle_chunk_data(const ResponseChunkData &chunk) = 0;
};

class Stream
{
 public:
   Stream(IResponseHandler *handler, RawStream stream);

   Stream(const Stream &)                = delete;
   Stream &operator=(const Stream &)     = delete;
   Stream(Stream &&) noexcept            = delete;
   Stream &operator=(Stream &&) noexcept = delete;

   void on_read(const Response &response);

   void send(const Request &req);

 private:
   IResponseHandler *m_handler;
   RawStream m_stream;
};

class StorageClient
{
 public:
   explicit StorageClient(ClientId client_id, IResponseHandler *handler,
                          const std::vector<std::string> &addresses);

   StorageClient(const StorageClient &)                = delete;
   StorageClient &operator=(const StorageClient &)     = delete;
   StorageClient(StorageClient &&) noexcept            = delete;
   StorageClient &operator=(StorageClient &&) noexcept = delete;

   void on_connected(RawStream stream);

   void subscribe_chunk(game::ChunkPosition position);
   void push_chunk(const world::Chunk &chunk);

   void await_connection();
   void wait();

 private:
   ClientId m_client_id{};

   std::vector<std::unique_ptr<Stream>> m_streams;
   IResponseHandler *m_handler{};

   std::shared_mutex m_streams_mutex;
   std::mutex m_cond_mutex;
   std::condition_variable m_connection_cond;

   ConnectionManager m_manager;
};

}// namespace minecpp::service::storage