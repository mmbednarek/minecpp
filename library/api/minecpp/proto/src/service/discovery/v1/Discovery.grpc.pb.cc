// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: minecpp/proto/service/discovery/v1/Discovery.proto

#include <minecpp/proto/service/discovery/v1/Discovery.pb.h>
#include <minecpp/proto/service/discovery/v1/Discovery.grpc.pb.h>

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace minecpp {
namespace proto {
namespace service {
namespace discovery {
namespace v1 {

static const char* DiscoveryService_method_names[] = {
  "/minecpp.proto.service.discovery.v1.DiscoveryService/Resolve",
  "/minecpp.proto.service.discovery.v1.DiscoveryService/RegisterService",
};

std::unique_ptr< DiscoveryService::Stub> DiscoveryService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< DiscoveryService::Stub> stub(new DiscoveryService::Stub(channel, options));
  return stub;
}

DiscoveryService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Resolve_(DiscoveryService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RegisterService_(DiscoveryService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status DiscoveryService::Stub::Resolve(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::DiscoveryRequest& request, ::minecpp::proto::service::discovery::v1::DiscoveryResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minecpp::proto::service::discovery::v1::DiscoveryRequest, ::minecpp::proto::service::discovery::v1::DiscoveryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Resolve_, context, request, response);
}

void DiscoveryService::Stub::async::Resolve(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::DiscoveryRequest* request, ::minecpp::proto::service::discovery::v1::DiscoveryResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minecpp::proto::service::discovery::v1::DiscoveryRequest, ::minecpp::proto::service::discovery::v1::DiscoveryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Resolve_, context, request, response, std::move(f));
}

void DiscoveryService::Stub::async::Resolve(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::DiscoveryRequest* request, ::minecpp::proto::service::discovery::v1::DiscoveryResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Resolve_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::discovery::v1::DiscoveryResponse>* DiscoveryService::Stub::PrepareAsyncResolveRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::DiscoveryRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minecpp::proto::service::discovery::v1::DiscoveryResponse, ::minecpp::proto::service::discovery::v1::DiscoveryRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Resolve_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::discovery::v1::DiscoveryResponse>* DiscoveryService::Stub::AsyncResolveRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::DiscoveryRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncResolveRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status DiscoveryService::Stub::RegisterService(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::RegisterRequest& request, ::minecpp::proto::service::discovery::v1::EmptyResult* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minecpp::proto::service::discovery::v1::RegisterRequest, ::minecpp::proto::service::discovery::v1::EmptyResult, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_RegisterService_, context, request, response);
}

void DiscoveryService::Stub::async::RegisterService(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::RegisterRequest* request, ::minecpp::proto::service::discovery::v1::EmptyResult* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minecpp::proto::service::discovery::v1::RegisterRequest, ::minecpp::proto::service::discovery::v1::EmptyResult, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RegisterService_, context, request, response, std::move(f));
}

void DiscoveryService::Stub::async::RegisterService(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::RegisterRequest* request, ::minecpp::proto::service::discovery::v1::EmptyResult* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RegisterService_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::discovery::v1::EmptyResult>* DiscoveryService::Stub::PrepareAsyncRegisterServiceRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::RegisterRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minecpp::proto::service::discovery::v1::EmptyResult, ::minecpp::proto::service::discovery::v1::RegisterRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_RegisterService_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::discovery::v1::EmptyResult>* DiscoveryService::Stub::AsyncRegisterServiceRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::discovery::v1::RegisterRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncRegisterServiceRaw(context, request, cq);
  result->StartCall();
  return result;
}

DiscoveryService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DiscoveryService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DiscoveryService::Service, ::minecpp::proto::service::discovery::v1::DiscoveryRequest, ::minecpp::proto::service::discovery::v1::DiscoveryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DiscoveryService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minecpp::proto::service::discovery::v1::DiscoveryRequest* req,
             ::minecpp::proto::service::discovery::v1::DiscoveryResponse* resp) {
               return service->Resolve(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DiscoveryService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DiscoveryService::Service, ::minecpp::proto::service::discovery::v1::RegisterRequest, ::minecpp::proto::service::discovery::v1::EmptyResult, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DiscoveryService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minecpp::proto::service::discovery::v1::RegisterRequest* req,
             ::minecpp::proto::service::discovery::v1::EmptyResult* resp) {
               return service->RegisterService(ctx, req, resp);
             }, this)));
}

DiscoveryService::Service::~Service() {
}

::grpc::Status DiscoveryService::Service::Resolve(::grpc::ServerContext* context, const ::minecpp::proto::service::discovery::v1::DiscoveryRequest* request, ::minecpp::proto::service::discovery::v1::DiscoveryResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DiscoveryService::Service::RegisterService(::grpc::ServerContext* context, const ::minecpp::proto::service::discovery::v1::RegisterRequest* request, ::minecpp::proto::service::discovery::v1::EmptyResult* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace minecpp
}  // namespace proto
}  // namespace service
}  // namespace discovery
}  // namespace v1

