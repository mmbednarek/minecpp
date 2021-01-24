#pragma once
#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <minepb/engine.grpc.pb.h>
#include <random>
#include <string>
#include <vector>
#include <map>

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
   std::vector<Service> m_services;
   std::map<uuid, int> m_uuid_to_id;
   std::default_random_engine m_random_engine{};

 public:
   static mb::result<Provider> create(const Config &cfg);

   Provider(std::vector<Service> services, std::map<uuid, int> id_map);

   [[nodiscard]] Service &get_random_service();
   [[nodiscard]] PlayerService &get_service_by_id(uuid id);
   [[nodiscard]] const std::vector<Service> &get_services() const;
};

}// namespace Engine::Client
