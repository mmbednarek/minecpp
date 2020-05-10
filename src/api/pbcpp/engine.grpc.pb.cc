// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: engine.proto

#include "engine.pb.h"
#include "engine.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace minecpp {
namespace engine {

static const char* PlayerService_method_names[] = {
  "/minecpp.engine.PlayerService/AcceptPlayer",
};

std::unique_ptr< PlayerService::Stub> PlayerService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< PlayerService::Stub> stub(new PlayerService::Stub(channel));
  return stub;
}

PlayerService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_AcceptPlayer_(PlayerService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status PlayerService::Stub::AcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::minecpp::engine::AcceptPlayerResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AcceptPlayer_, context, request, response);
}

void PlayerService::Stub::experimental_async::AcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest* request, ::minecpp::engine::AcceptPlayerResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AcceptPlayer_, context, request, response, std::move(f));
}

void PlayerService::Stub::experimental_async::AcceptPlayer(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::minecpp::engine::AcceptPlayerResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AcceptPlayer_, context, request, response, std::move(f));
}

void PlayerService::Stub::experimental_async::AcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest* request, ::minecpp::engine::AcceptPlayerResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_AcceptPlayer_, context, request, response, reactor);
}

void PlayerService::Stub::experimental_async::AcceptPlayer(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::minecpp::engine::AcceptPlayerResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_AcceptPlayer_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minecpp::engine::AcceptPlayerResponse>* PlayerService::Stub::AsyncAcceptPlayerRaw(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::minecpp::engine::AcceptPlayerResponse>::Create(channel_.get(), cq, rpcmethod_AcceptPlayer_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::minecpp::engine::AcceptPlayerResponse>* PlayerService::Stub::PrepareAsyncAcceptPlayerRaw(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::minecpp::engine::AcceptPlayerResponse>::Create(channel_.get(), cq, rpcmethod_AcceptPlayer_, context, request, false);
}

PlayerService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      PlayerService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< PlayerService::Service, ::minecpp::engine::AcceptPlayerRequest, ::minecpp::engine::AcceptPlayerResponse>(
          std::mem_fn(&PlayerService::Service::AcceptPlayer), this)));
}

PlayerService::Service::~Service() {
}

::grpc::Status PlayerService::Service::AcceptPlayer(::grpc::ServerContext* context, const ::minecpp::engine::AcceptPlayerRequest* request, ::minecpp::engine::AcceptPlayerResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace minecpp
}  // namespace engine

