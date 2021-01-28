#include "provider.h"
#include <algorithm>
#include <grpcpp/create_channel.h>
#include <minecpp/util/uuid.h>

namespace Engine::Client {

mb::result<Provider> Provider::create(const Config &cfg) {
   if (cfg.addresses.empty()) {
      return mb::error("no engine addresses provided");
   }

   std::map<uuid, int> uuid_to_id;

   std::vector<Service> services;
   services.reserve(cfg.addresses.size());

   try {
      std::transform(cfg.addresses.begin(), cfg.addresses.end(), std::back_inserter(services), [&uuid_to_id, service_count = 0](const std::string &adr) mutable {
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
        minecpp::util::decode_uuid(id, res.id().data());
        uuid_to_id[id] = service_count++;

        return Service{
                .channel = channel,
                .service = std::move(stub),
                .id = id,
        };
      });
   } catch (const std::runtime_error &e) {
      return mb::error(e.what());
   }

   return Provider(std::move(services), std::move(uuid_to_id));
}

Provider::Provider(std::vector<Service> services, std::map<uuid, int> uuid_to_id) : m_services(std::move(services)), m_uuid_to_id(std::move(uuid_to_id)) {}

Provider::Service &Provider::get_random_service() {
   assert(!m_services.empty());
   std::uniform_int_distribution<int> dist(0, m_services.size() - 1);
   return m_services.at(dist(m_random_engine));
}

PlayerService &Provider::get_service_by_id(uuid id) {
   auto iter = m_uuid_to_id.find(id);
   if (iter == m_uuid_to_id.end()) {
      throw std::runtime_error("invalid service id");
   }
   return m_services.at(iter->second).service;
}

const std::vector<Provider::Service> &Provider::get_services() const {
   return m_services;
}

}// namespace Engine::Client
