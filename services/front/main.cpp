#include "config.h"
#include "consumer.h"
#include "players.h"
#include "protocol/login_handler.h"
#include "protocol/play_handler.h"
#include "protocol/status_handler.h"
#include "server.h"
#include <atomic>
#include <spdlog/spdlog.h>
#include <thread>

using namespace Front;

auto main() -> int {
   auto conf = get_config();
   std::atomic_bool consume_messages = true;

   Service service(conf);

   Protocol::StatusHandler status_handler;
   Protocol::PlayHandler play_handler(service);
   Protocol::LoginHandler login_handler(service, play_handler);

   std::vector<std::string> topics{"minecpp"};

   boost::asio::io_context ctx;
   Server svr(ctx, conf.port, dynamic_cast<Protocol::Handler *>(&play_handler),
              dynamic_cast<Protocol::Handler *>(&status_handler),
              dynamic_cast<Protocol::Handler *>(&login_handler));

   Consumer consumer(
       KafkaSettings{
           .client_name = "front",
           .group = "front",
           .hosts = conf.kafka_hosts,
           .topics = topics,
       },
       svr);

   std::thread kafka_thread([&consumer, &consume_messages] {
      while (consume_messages.load()) {
         consumer.consume([](KafkaBuff key, KafkaBuff value) {
            std::string_view contents(value.data, value.size);
            spdlog::info("received kafka message: ", contents);
         });
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