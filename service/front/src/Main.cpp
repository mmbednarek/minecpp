#include "Config.h"
#include "EventHandler.h"
#include "protocol/LoginHandler.h"
#include "protocol/PlayHandler.h"
#include "protocol/StatusHandler.h"
#include "Server.h"
#include "Ticks.h"
#include <atomic>
#include <minecpp/repository/Repository.h>
#include <spdlog/spdlog.h>
#include <thread>

using namespace minecpp::service::front;
using minecpp::service::engine::Client;

auto main() -> int
{
   auto conf = get_config();

   auto registry = minecpp::repository::load_network_registry_from_file(conf.registry_path).unwrap({});

   Service service(conf);

   Protocol::StatusHandler status_handler;
   Protocol::PlayHandler play_handler(service);
   Protocol::LoginHandler login_handler(service, play_handler);

   boost::asio::io_context ctx;
   Server svr(ctx, static_cast<short>(conf.port), dynamic_cast<Protocol::Handler *>(&play_handler),
              dynamic_cast<Protocol::Handler *>(&status_handler),
              dynamic_cast<Protocol::Handler *>(&login_handler));

   EventHandler handler(svr, registry);
   Client engine_client(conf.engine_hosts, handler);

   service.set_stream(&engine_client);
   handler.set_stream(&engine_client);

   spdlog::info("established connection to all engine hosts");

   TickManager ticks(svr);
   std::thread ticks_thread([&ticks]() { ticks.tick(); });

   spdlog::info("starting TCP server on address 0.0.0.0:{}", conf.port);

   try {
      ctx.run();
   } catch (std::exception &e) {
      spdlog::error("SERVER CRASHED: {}", e.what());
   }
   return 0;
}