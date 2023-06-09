#include <minecpp/game/ChunkPosition.h>
#include <minecpp/service/storage/Storage.h>
#include <minecpp/world/Chunk.h>
#include <spdlog/spdlog.h>

using minecpp::service::storage::IResponseHandler;
using minecpp::service::storage::ResponseChunkData;
using minecpp::service::storage::StorageClient;
using minecpp::world::Chunk;

class Handler : public IResponseHandler
{
 public:
   void handle_response(minecpp::service::storage::Response response) override
   {
      switch (response.message_case()) {
      case minecpp::proto::service::storage::v1::Response::kChunkData:
         Handler::handle_chunk_data(response.chunk_data());
         break;
      default: break;
      }
   }

   static void handle_chunk_data(const ResponseChunkData &proto_chunk)
   {
      auto chunk = Chunk::from_proto(proto_chunk.chunk_data());
      spdlog::info("obtained chunk data {}, {}", chunk->position().x(), chunk->position().z());
      spdlog::info("block at 1 2 3: {}", *chunk->block_at({1, 2, 3}));
   }
};

int main()
{
   Handler handler;

   StorageClient client{0, handler};

   client.subscribe_chunk({1, 2});

   spdlog::info("exiting");
}