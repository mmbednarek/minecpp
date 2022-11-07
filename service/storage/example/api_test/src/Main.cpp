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
   void handle_chunk_data(const ResponseChunkData &proto_chunk) override
   {
      auto chunk = Chunk::from_proto(proto_chunk.chunk_data());
      spdlog::info("obtained chunk data {}, {}", chunk.pos().x, chunk.pos().z);
      spdlog::info("block at 1 2 3: {}", *chunk.get_block({1, 2, 3}));
   }

   void handle_empty_chunk(const minecpp::service::storage::ResponseEmptyChunk &chunk) override {}
};

int main()
{
   Handler handler;

   StorageClient client{0, &handler, {"127.0.0.1:7000"}};

   //   Chunk chunk{1, 2, {}};
   //   chunk.set_block({1, 2, 3}, 2137);

   //   client.push_chunk(chunk);
   client.subscribe_chunk({1, 2});

   client.wait();

   spdlog::info("exiting");
}