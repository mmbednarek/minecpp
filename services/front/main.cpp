#include "players.h"
#include "protocol/login_handler.h"
#include "protocol/play_handler.h"
#include "protocol/status_handler.h"
#include "server.h"
#include <boost/log/trivial.hpp>
#include <grpcpp/grpcpp.h>
#include <yaml-cpp/yaml.h>

using namespace Front;

auto main() -> int {
   std::string cfg_filename = std::getenv("CONFIG_FILE");
   if (cfg_filename.empty()) {
      cfg_filename = "config.yml";
   }

   YAML::Node config = YAML::LoadFile(cfg_filename);
   auto engine_address = config["engine_address"].as<std::string>();

   auto port = config["front_port"].as<int>();
   if (!port) {
      port = 4001;
   }

   auto engine_chan =
       grpc::CreateChannel(engine_address, grpc::InsecureChannelCredentials());

   BOOST_LOG_TRIVIAL(info) << "starting server on port " << port;


   PlayerManager player_manager;
   Service service(player_manager, engine_chan);

   Protocol::StatusHandler status_handler;
   Protocol::PlayHandler play_handler;
   Protocol::LoginHandler login_handler(service);

   try {
      boost::asio::io_context ctx;
      Server svr(ctx, port, dynamic_cast<Protocol::Handler *>(&play_handler),
                 dynamic_cast<Protocol::Handler *>(&status_handler),
                 dynamic_cast<Protocol::Handler *>(&login_handler));
      ctx.run();
   } catch (std::exception &e) {
      BOOST_LOG_TRIVIAL(error) << "server crash " << e.what();
   }
}