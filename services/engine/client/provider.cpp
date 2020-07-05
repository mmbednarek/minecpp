#include "provider.h"
#include <grpcpp/create_channel.h>
#include <mineutils/uuid.h>

namespace Engine::Client {

Provider::Provider(Config &cfg) {
   assert(!cfg.addresses.empty());

   services.reserve(cfg.addresses.size());

   for (const auto &adr : cfg.addresses) {
      auto channel =
          grpc::CreateChannel(adr, grpc::InsecureChannelCredentials());

      auto stub = minecpp::engine::PlayerService::NewStub(channel);

      grpc::ClientContext ctx;
      minecpp::engine::EmptyRequest req;
      minecpp::engine::GetServiceIdResponse res;
      auto status = stub->GetServiceId(&ctx, req, &res);
      if (!status.ok()) {
         throw std::runtime_error("failed to connect to engine service");
      }
      uuid id{};
      Utils::decode_uuid(id, res.id().data());
      id_map[id] = services.size();

      services.emplace_back(Service{
          .channel = channel,
          .service = std::move(stub),
          .id = id,
      });
   }
}

Provider::Service &Provider::get_random_service() {
   assert(!services.empty());
   std::uniform_int_distribution<int> dist(0, services.size() - 1);
   return services[dist(rand)];
}

PlayerService &Provider::get_service_by_id(uuid id) {
   auto iter = id_map.find(id);
   if (iter == id_map.end()) {
      throw std::runtime_error("invalid service id");
   }
   return services[iter->second].service;
}

const std::vector<Provider::Service> &Provider::get_services() {
   return services;
}

} // namespace Engine::Client
