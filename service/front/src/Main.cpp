#include "Config.h"
#include "EventHandler.h"
#include "mb/core.h"
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
   auto cfg_filename = mb::getenv("CONFIG_FILE").unwrap("config.yaml");

   auto conf = get_config(cfg_filename);

   if (conf.debug_logger) {
      spdlog::set_level(spdlog::level::debug);
   }

   auto registry = minecpp::repository::load_network_registry_from_file(conf.resources_registry).unwrap({});

   Service service(conf);

   Protocol::StatusHandler status_handler;
   Protocol::PlayHandler play_handler(service);
   Protocol::LoginHandler login_handler(service, play_handler);

   boost::asio::io_context ctx;
   Server svr(ctx, static_cast<mb::u16>(conf.server_bind_port),
              dynamic_cast<Protocol::Handler *>(&play_handler),
              dynamic_cast<Protocol::Handler *>(&status_handler),
              dynamic_cast<Protocol::Handler *>(&login_handler));

   EventHandler handler(svr, registry);
   Client engine_client(conf.engine_endpoints, handler);

   service.set_stream(&engine_client);
   handler.set_stream(&engine_client);

   spdlog::info("established connection to all engine hosts");

   TickManager ticks(svr);
   std::thread ticks_thread([&ticks]() { ticks.tick(); });

   spdlog::info("starting TCP server on address {}:{}", conf.server_bind_address, conf.server_bind_port);

   try {
      ctx.run();
   } catch (std::exception &e) {
      spdlog::error("SERVER CRASHED: {}", e.what());
   }
   return 0;
}