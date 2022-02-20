#include "config.h"
#include "event_handler.h"
#include "protocol/login_handler.h"
#include "protocol/play_handler.h"
#include "protocol/status_handler.h"
#include "server.h"
#include "ticks.h"
#include <atomic>
#include <grpcpp/grpcpp.h>
#include <spdlog/spdlog.h>
#include <thread>

using namespace minecpp::service::front;

auto main() -> int {
   auto conf = get_config();

   auto chunk_channel = grpc::CreateChannel(conf.chunk_storage_host, grpc::InsecureChannelCredentials());
   std::shared_ptr<minecpp::proto::service::chunk_storage::v1::ChunkStorage::Stub> chunk_service =
           minecpp::proto::service::chunk_storage::v1::ChunkStorage::NewStub(chunk_channel);

   Service service(conf, chunk_service);

   Protocol::StatusHandler status_handler;
   Protocol::PlayHandler play_handler(service);
   Protocol::LoginHandler login_handler(service, play_handler);

   boost::asio::io_context ctx;
   Server svr(ctx, static_cast<short>(conf.port), dynamic_cast<Protocol::Handler *>(&play_handler),
              dynamic_cast<Protocol::Handler *>(&status_handler), dynamic_cast<Protocol::Handler *>(&login_handler));

   EventHandler handler(svr);
   minecpp::service::engine::Client engine_client(conf.engine_hosts[0], handler);

   spdlog::info("attempting to connect to engine");

   auto stream = engine_client.join();
   service.set_stream(&stream);
   handler.set_stream(&stream);

   spdlog::info("established connection, starting tick");

   TickManager ticks(svr, chunk_service);
   std::thread ticks_thread([&ticks]() { ticks.tick(); });

   spdlog::info("starting server on port {}", conf.port);

   try {
      ctx.run();
   } catch (std::exception &e) {
      spdlog::error("SERVER CRASHED: {}", e.what());
   }
   return 0;
}