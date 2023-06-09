#include "Config.h"
#include "EventHandler.h"
#include "protocol/LoginHandler.h"
#include "protocol/PlayHandler.h"
#include "protocol/StatusHandler.h"
#include "Server.h"
#include "Ticks.h"

#include "minecpp/network/Network.h"
#include "minecpp/repository/Repository.h"

#include <atomic>
#include <mb/core.h>
#include <spdlog/spdlog.h>
#include <thread>

using namespace minecpp::service::front;
using minecpp::service::engine::Client;

auto main() -> int
{
   auto config_filename = mb::getenv("CONFIG_FILE").unwrap("config.yaml");
   auto config          = get_config(config_filename);

   if (config.debug_logger) {
      spdlog::set_level(spdlog::level::debug);
   }

   auto registry = minecpp::repository::load_network_registry_from_file(config.resources_registry).unwrap({});

   Service service(config);

   std::unique_ptr<minecpp::crypto::PrivateKey> private_key;
   if (config.encryption_enabled) {
      if (config.encryption_private_key.empty()) {
         private_key = std::make_unique<minecpp::crypto::PrivateKey>(1024);
      } else {
         private_key = std::make_unique<minecpp::crypto::PrivateKey>(config.encryption_private_key,
                                                                     config.encryption_pass_phrase);
      }
   }

   protocol::StatusHandler status_handler;
   protocol::PlayHandler play_handler(service);
   protocol::LoginHandler login_handler(service, play_handler, private_key.get());

   boost::asio::io_context ctx;
   Server svr(ctx, static_cast<mb::u16>(config.server_bind_port),
              dynamic_cast<protocol::Handler *>(&play_handler),
              dynamic_cast<protocol::Handler *>(&status_handler),
              dynamic_cast<protocol::Handler *>(&login_handler));

   EventHandler handler(svr, registry);
   Client engine_client(handler);
   engine_client.tick();

   service.set_client(&engine_client);
   handler.set_client(&engine_client);

   spdlog::info("established connection to all engine hosts");

   TickManager ticks(svr, engine_client);
   std::thread ticks_thread([&ticks]() { ticks.tick(); });

   for (const auto &endpoint_str : config.engine_endpoints) {
      auto endpoint = minecpp::network::Endpoint::from_host(endpoint_str);
      if (endpoint.has_failed()) {
         spdlog::error("failed to resolve host: {}", endpoint_str);
         return 1;
      }
      engine_client.connect(*endpoint);
   }

   spdlog::info("starting TCP server on address {}:{}", config.server_bind_address, config.server_bind_port);

   try {
      ctx.run();
   } catch (std::exception &e) {
      spdlog::error("SERVER CRASHED: {}", e.what());
   }
   return 0;
}