#pragma once
#include <minepb/events.pb.h>
#include <functional>
#include <cppkafka/cppkafka.h>
#include <string>
#include <vector>
#include "server.h"

namespace Front {

using namespace minecpp::events;

struct KafkaSettings {
   std::string client_name;
   std::string group;
   std::string hosts;
   std::vector<std::string> &topics;
};

struct KafkaBuff {
   std::size_t size;
   const char *data;
};

using KafkaHandler = std::function<void(KafkaBuff, KafkaBuff)>;

class Consumer {
   cppkafka::Consumer *consumer = nullptr;
   Server &server;

 public:
   Consumer(KafkaSettings settings, Server &server);

   void consume(KafkaHandler handler);

   void on_event(EntityMove &pos);
   void on_event(EntityLook &pos);
   void on_event(SpawnPlayer &pos);
   void on_event(Chat &pos);
};

} // namespace Front
