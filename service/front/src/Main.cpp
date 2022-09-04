#include "Config.h"
#include "EventHandler.h"
#include "protocol/LoginHandler.h"
#include "protocol/PlayHandler.h"
#include "protocol/StatusHandler.h"
#include "Server.h"
#include "Ticks.h"
#include <atomic>
#include <grpcpp/grpcpp.h>
#include <minecpp/repository/Repository.h>
#include <spdlog/spdlog.h>
#include <thread>

using namespace minecpp::service::front;
using minecpp::service::engine::Client;

auto main() -> int
{
   auto conf = get_config();

   auto registry = minecpp::repository::load_network_registry_from_file(conf.registry_path).unwrap({});

   auto chunk_channel = grpc::CreateChannel(conf.chunk_storage_host, grpc::InsecureChannelCredentials());
   std::shared_ptr<minecpp::proto::service::chunk_storage::v1::ChunkStorage::Stub> chunk_service =
           minecpp::proto::service::chunk_storage::v1::ChunkStorage::NewStub(chunk_channel);

   Service service(conf, chunk_service);

   Protocol::StatusHandler status_handler;
   Protocol::PlayHandler play_handler(service);
   Protocol::LoginHandler login_handler(service, play_handler);

   boost::asio::io_context ctx;
   Server svr(ctx, static_cast<short>(conf.port), dynamic_cast<Protocol::Handler *>(&play_handler),
              dynamic_cast<Protocol::Handler *>(&status_handler),
              dynamic_cast<Protocol::Handler *>(&login_handler));

   EventHandler handler(svr, registry);
   Client engine_client(conf.engine_hosts, handler);

   spdlog::info("attempting to connect to engine");

   service.set_stream(&engine_client);
   handler.set_stream(&engine_client);

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