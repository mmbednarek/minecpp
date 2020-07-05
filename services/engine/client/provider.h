#pragma once
#include <boost/uuid/uuid.hpp>
#include <map>
#include <minepb/engine.grpc.pb.h>
#include <random>
#include <string>
#include <vector>

namespace Engine::Client {

struct Config {
   std::vector<std::string> addresses;
};

using PlayerService = std::unique_ptr<minecpp::engine::PlayerService::Stub>;
using boost::uuids::uuid;

class Provider {
 public:
   struct Service {
      std::shared_ptr<grpc::ChannelInterface> channel;
      PlayerService service;
      int player_count = 0;
      uuid id{};
   };

 private:
   std::vector<Service> services;
   std::map<uuid, int> id_map;
   std::default_random_engine rand{};

 public:
   explicit Provider(Config &cfg);

   Service &get_random_service();
   PlayerService &get_service_by_id(uuid id);
   const std::vector<Service> &get_services();
};

} // namespace Engine::Client
