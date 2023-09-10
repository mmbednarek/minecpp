#include <minecpp/game/ChunkPosition.h>
#include <minecpp/service/storage/Storage.h>
#include <minecpp/world/Chunk.h>
#include <spdlog/spdlog.h>

using minecpp::service::storage::IResponseHandler;
using minecpp::service::storage::StorageClient;
using minecpp::world::Chunk;

char map_height(int height)
{
   static constexpr std::array<char, 8> values{' ', '.', '-', ':', '/', '%', '&', '#'};
   auto level = height / 8;
   if (level >= 8)
      return '@';

   return values[static_cast<std::size_t>(level)];
}

class Handler : public IResponseHandler
{
 public:
   void on_reply_empty_chunk(int /*a*/, const minecpp::net::storage::cb::ReplyEmptyChunk &message) override
   {
      spdlog::info("reply: empty chunk {} {}", message.position.x(), message.position.y());
   }

   void on_reply_chunk(int /*a*/, const minecpp::net::storage::cb::ReplyChunk &message) override
   {
      Chunk chunk;
      chunk.read_net_chunk(message.chunk);

      spdlog::info("reply: chunk data {} {}: ", chunk.position().x(), chunk.position().z());

      for (int y = 0; y < 16; ++y) {
         for (int x = 0; x < 16; ++x) {
            auto height = chunk.height_at(x, y);
            std::cout << map_height(height);
         }
         std::cout << '\n';
      }

      spdlog::info("reply: block at 8 8 40 {}", *chunk.block_at({8, 40, 8}));
   }

   void on_failure(int /*a*/, std::uint8_t msg_code) override
   {
      spdlog::info("reply: invalid message code: {}", msg_code);
   }
};

int main()
{
   Handler handler;

   auto endpoint = minecpp::network::Endpoint::from_host("127.0.0.1");
   if (endpoint.has_failed())
      return 1;

   StorageClient client{0, handler};
   client.connect(*endpoint);

   for (int i{0}; i < 10; ++i) {
      using namespace std::chrono_literals;

      client.tick();
      std::this_thread::sleep_for(50ms);
   }

   client.subscribe_chunk({3, 2});

   for (;;) {
      using namespace std::chrono_literals;

      client.tick();
      std::this_thread::sleep_for(50ms);
   }
}