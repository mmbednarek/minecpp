#include "../engine/client/provider.h"
#include "config.h"
#include "event_handler.h"
#include "protocol/login_handler.h"
#include "protocol/play_handler.h"
#include "protocol/status_handler.h"
#include "server.h"
#include "ticks.h"
#include <atomic>
#include <grpcpp/grpcpp.h>
#include <minepb/engine.grpc.pb.h>
#include <spdlog/spdlog.h>
#include <thread>

using namespace Front;

auto main() -> int {
   auto conf = get_config();
   std::atomic_bool consume_messages = true;

   Engine::Client::Config engine_cfg{
       .addresses = conf.engine_hosts,
   };
   Engine::Client::Provider engine_provider(engine_cfg);

   auto chunk_channel = grpc::CreateChannel(conf.chunk_storage_host, grpc::InsecureChannelCredentials());
   std::shared_ptr<minecpp::chunk_storage::ChunkStorage::Stub> chunk_service =
       minecpp::chunk_storage::ChunkStorage::NewStub(chunk_channel);

   Service service(conf, engine_provider, chunk_service);

   Protocol::StatusHandler status_handler;
   Protocol::PlayHandler play_handler(service);
   Protocol::LoginHandler login_handler(service, play_handler);

   std::vector<std::string> topics{"minecpp"};

   boost::asio::io_context ctx;
   Server svr(ctx, conf.port, dynamic_cast<Protocol::Handler *>(&play_handler),
              dynamic_cast<Protocol::Handler *>(&status_handler), dynamic_cast<Protocol::Handler *>(&login_handler));

   TickManager ticks(svr, chunk_service);

   std::thread ticks_thread([&ticks]() { ticks.tick(); });

   std::vector<std::thread> event_threads;
   EventHandler consumer(svr);
   minecpp::engine::FetchEventsRequest req{};
   req.set_front_id(conf.front_id);
   for (auto const &engine : engine_provider.get_services()) {
      event_threads.emplace_back(std::thread([&engine, &consumer, req] {
         grpc::ClientContext ctx{};
         auto reader = engine.service->FetchEvents(&ctx, req);

         minecpp::engine::Event event{};
         while (reader->Read(&event)) {
            consumer.accept_event(event);
         }
      }));
   }

   spdlog::info("starting server on port {}", conf.port);

   try {
      ctx.run();
   } catch (std::exception &e) {
      spdlog::error("SERVER CRASHED: {}", e.what());
   }

   consume_messages = false;
   return 0;
}