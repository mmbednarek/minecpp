#ifndef MINECPP_API_H
#define MINECPP_API_H
#include <grpc++/grpc++.h>
#include <mb/int.h>
#include <mb/result.h>
#include <memory>
#include <minecpp/proto/service/discovery/v1/discovery.grpc.pb.h>
#include <string>
#include <string_view>
#include <vector>

namespace minecpp::service::discovery {

using ResourceVersion = mb::u64;

struct Endpoint
{
   std::string address{};
   mb::u32 port{};

   [[nodiscard]] std::string to_string() const;
   [[nodiscard]] proto::service::discovery::v1::Endpoint to_proto() const;

   static Endpoint from_proto(const proto::service::discovery::v1::Endpoint &endpoint);
};

struct DiscoveryResponse
{
   bool modified{};
   std::vector<Endpoint> endpoints{};
};

class Client
{
   std::shared_ptr<grpc::ChannelInterface> m_channel;
   std::unique_ptr<proto::service::discovery::v1::DiscoveryService::Stub> m_stub;
   ResourceVersion m_last_resource_version{};

 public:
   static mb::result<Client> create(std::string_view address);

   mb::result<DiscoveryResponse> resolve(std::string_view service_name);
   mb::result<mb::empty> register_service(std::string_view service_name, std::string_view address,
                                          mb::u32 port);

 private:
   Client(std::shared_ptr<grpc::ChannelInterface> channel,
          std::unique_ptr<proto::service::discovery::v1::DiscoveryService::Stub> stub);
};

}// namespace minecpp::service::discovery

#endif//MINECPP_API_H
