#include "config.h"
#include "event_handler.h"
#include "keepalive.h"
#include "players.h"
#include "protocol/login_handler.h"
#include "protocol/play_handler.h"
#include "protocol/status_handler.h"
#include "server.h"
#include <atomic>
#include <grpcpp/grpcpp.h>
#include <minepb/engine.grpc.pb.h>
#include <spdlog/spdlog.h>
#include <thread>

using namespace Front;

auto main() -> int {
   auto conf = get_config();
   std::atomic_bool consume_messages = true;

   auto channel = grpc::CreateChannel(conf.engine_hosts[0],
                                      grpc::InsecureChannelCredentials());
   auto player_service = minecpp::engine::PlayerService::NewStub(channel);

   Service service(conf, player_service);

   Protocol::StatusHandler status_handler;
   Protocol::PlayHandler play_handler(service);
   Protocol::LoginHandler login_handler(service, play_handler);

   std::vector<std::string> topics{"minecpp"};

   boost::asio::io_context ctx;
   Server svr(ctx, conf.port, dynamic_cast<Protocol::Handler *>(&play_handler),
              dynamic_cast<Protocol::Handler *>(&status_handler),
              dynamic_cast<Protocol::Handler *>(&login_handler));

   std::thread keepalive_thread([&svr]() { keepalive_update(svr); });

   std::thread event_thread([conf, &svr, &player_service] {
      grpc::ClientContext ctx;
      minecpp::engine::FetchEventsRequest req;
      req.set_front_id(conf.front_id);

      auto reader = player_service->FetchEvents(&ctx, req);

      EventHandler consumer(svr);

      minecpp::engine::Event event;
      while (reader->Read(&event)) {
         consumer.accept_event(event);
      }
   });
   spdlog::info("starting server on port {}", conf.port);

   try {
      ctx.run();
   } catch (std::exception &e) {
      spdlog::error("SERVER CRASHED: {}", e.what());
   }

   consume_messages = false;
   return 0;
}