#pragma once
#include "cache.h"
#include <minecpp/proto/service/discovery/v1/discovery.grpc.pb.h>

namespace minecpp::service::discovery {

class Service final : public proto::service::discovery::v1::DiscoveryService::Service {
   Cache m_cache;

 public:
   grpc::Status Resolve(::grpc::ServerContext *context, const ::minecpp::proto::service::discovery::v1::DiscoveryRequest *request, ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response) override;
   grpc::Status RegisterService(::grpc::ServerContext *context, const ::minecpp::proto::service::discovery::v1::RegisterRequest *request, ::minecpp::proto::service::discovery::v1::EmptyResult *response) override;
};

}// namespace minecpp::service::discovery
