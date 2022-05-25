#include <fmt/format.h>
#include <minecpp/service/discovery/api.h>

namespace minecpp::service::discovery {

namespace proto_discovery_v1 = proto::service::discovery::v1;

Client::Client(std::shared_ptr<grpc::ChannelInterface> channel,
               std::unique_ptr<proto_discovery_v1::DiscoveryService::Stub> stub) :
    m_channel(std::move(channel)),
    m_stub(std::move(stub))
{
}

mb::result<Client> Client::create(std::string_view address)
{
   auto channel = grpc::CreateChannel(std::string(address), grpc::InsecureChannelCredentials());
   auto stub    = proto_discovery_v1::DiscoveryService::NewStub(channel);
   return Client(std::move(channel), std::move(stub));
}

mb::result<DiscoveryResponse> Client::resolve(std::string_view service_name)
{
   grpc::ClientContext ctx;
   proto_discovery_v1::DiscoveryRequest request{};
   request.set_resource_version(m_last_resource_version);
   request.set_service_name(std::string(service_name));

   proto_discovery_v1::DiscoveryResponse response{};

   auto status = m_stub->Resolve(&ctx, request, &response);
   if (!status.ok()) {
      return mb::error(fmt::format("could not resolve service {}: {}", service_name, status.error_message()));
   }

   if (response.resource_version() == m_last_resource_version) {
      return DiscoveryResponse{
              .modified = false,
      };
   }

   DiscoveryResponse result{.modified = true};
   result.endpoints.reserve(response.endpoints_size());
   std::transform(
           response.endpoints().begin(), response.endpoints().end(), std::back_inserter(result.endpoints),
           [](const proto_discovery_v1::Endpoint &endpoint) { return Endpoint::from_proto(endpoint); });
   return std::move(result);// must be fed into result
}

mb::result<mb::empty> Client::register_service(std::string_view service_name, std::string_view address,
                                               mb::u32 port)
{
   grpc::ClientContext ctx;
   proto_discovery_v1::RegisterRequest request{};
   request.set_service_name(std::string(service_name));
   request.mutable_endpoint()->set_address(std::string(address));
   request.mutable_endpoint()->set_port(port);

   proto_discovery_v1::EmptyResult response{};
   auto status = m_stub->RegisterService(&ctx, request, &response);
   if (!status.ok()) {
      return mb::error(
              fmt::format("could not register service {}: {}", service_name, status.error_message()));
   }

   return mb::ok;
}

std::string Endpoint::to_string() const
{
   return fmt::format("{}:{}", address, port);
}

proto::service::discovery::v1::Endpoint Endpoint::to_proto() const
{
   proto::service::discovery::v1::Endpoint result;
   result.set_address(address);
   result.set_port(port);
   return result;
}

Endpoint Endpoint::from_proto(const proto::service::discovery::v1::Endpoint &endpoint)
{
   return Endpoint{
           .address = endpoint.address(),
           .port    = endpoint.port(),
   };
}

}// namespace minecpp::service::discovery
