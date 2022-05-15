#include "service.h"
#include "cache.h"
#include <spdlog/spdlog.h>

namespace minecpp::service::discovery {

grpc::Status Service::Resolve(::grpc::ServerContext *context,
                              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest *request,
                              ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response)
{
   if (request->resource_version() == m_cache.resource_version()) {
      response->set_resource_version(request->resource_version());
      return {};
   }
   response->set_resource_version(m_cache.resource_version());

   auto lookup_result = m_cache.lookup(request->service_name());

   response->mutable_endpoints()->Reserve(static_cast<int>(lookup_result.size()));
   for (const auto &endpoint : lookup_result) {
      response->mutable_endpoints()->Add(endpoint.to_proto());
   }

   return {};
}

grpc::Status
Service::RegisterService(::grpc::ServerContext *context,
                         const ::minecpp::proto::service::discovery::v1::RegisterRequest *request,
                         ::minecpp::proto::service::discovery::v1::EmptyResult *response)
{
   auto endpoint = Endpoint::from_proto(request->endpoint());
   spdlog::info("registering endpoint {} for service {}", endpoint.to_string(), request->service_name());
   m_cache.add(request->service_name(), endpoint);
   return {};
}

}// namespace minecpp::service::discovery