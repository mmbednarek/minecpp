// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: minecpp/proto/service/chunk_storage/v1/ChunkStorage.proto

#include <minecpp/proto/service/chunk_storage/v1/ChunkStorage.pb.h>
#include <minecpp/proto/service/chunk_storage/v1/ChunkStorage.grpc.pb.h>

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace minecpp {
namespace proto {
namespace service {
namespace chunk_storage {
namespace v1 {

static const char* ChunkStorage_method_names[] = {
  "/minecpp.proto.service.chunk_storage.v1.ChunkStorage/LoadChunk",
  "/minecpp.proto.service.chunk_storage.v1.ChunkStorage/SetBlock",
  "/minecpp.proto.service.chunk_storage.v1.ChunkStorage/AddReferences",
  "/minecpp.proto.service.chunk_storage.v1.ChunkStorage/RemoveReference",
  "/minecpp.proto.service.chunk_storage.v1.ChunkStorage/HeightAt",
  "/minecpp.proto.service.chunk_storage.v1.ChunkStorage/GetBlock",
};

std::unique_ptr< ChunkStorage::Stub> ChunkStorage::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ChunkStorage::Stub> stub(new ChunkStorage::Stub(channel, options));
  return stub;
}

ChunkStorage::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_LoadChunk_(ChunkStorage_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SetBlock_(ChunkStorage_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_AddReferences_(ChunkStorage_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RemoveReference_(ChunkStorage_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_HeightAt_(ChunkStorage_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetBlock_(ChunkStorage_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ChunkStorage::Stub::LoadChunk(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest& request, ::minecpp::proto::chunk::v1::Chunk* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest, ::minecpp::proto::chunk::v1::Chunk, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_LoadChunk_, context, request, response);
}

void ChunkStorage::Stub::async::LoadChunk(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest* request, ::minecpp::proto::chunk::v1::Chunk* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest, ::minecpp::proto::chunk::v1::Chunk, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_LoadChunk_, context, request, response, std::move(f));
}

void ChunkStorage::Stub::async::LoadChunk(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest* request, ::minecpp::proto::chunk::v1::Chunk* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_LoadChunk_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::chunk::v1::Chunk>* ChunkStorage::Stub::PrepareAsyncLoadChunkRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minecpp::proto::chunk::v1::Chunk, ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_LoadChunk_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::chunk::v1::Chunk>* ChunkStorage::Stub::AsyncLoadChunkRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncLoadChunkRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ChunkStorage::Stub::SetBlock(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest& request, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SetBlock_, context, request, response);
}

void ChunkStorage::Stub::async::SetBlock(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest* request, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SetBlock_, context, request, response, std::move(f));
}

void ChunkStorage::Stub::async::SetBlock(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest* request, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SetBlock_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::chunk_storage::v1::EmptyResponse>* ChunkStorage::Stub::PrepareAsyncSetBlockRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minecpp::proto::service::chunk_storage::v1::EmptyResponse, ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SetBlock_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::chunk_storage::v1::EmptyResponse>* ChunkStorage::Stub::AsyncSetBlockRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSetBlockRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ChunkStorage::Stub::AddReferences(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest& request, ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest, ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_AddReferences_, context, request, response);
}

void ChunkStorage::Stub::async::AddReferences(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest* request, ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest, ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddReferences_, context, request, response, std::move(f));
}

void ChunkStorage::Stub::async::AddReferences(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest* request, ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddReferences_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse>* ChunkStorage::Stub::PrepareAsyncAddReferencesRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse, ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_AddReferences_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse>* ChunkStorage::Stub::AsyncAddReferencesRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncAddReferencesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ChunkStorage::Stub::RemoveReference(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest& request, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_RemoveReference_, context, request, response);
}

void ChunkStorage::Stub::async::RemoveReference(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest* request, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RemoveReference_, context, request, response, std::move(f));
}

void ChunkStorage::Stub::async::RemoveReference(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest* request, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RemoveReference_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::chunk_storage::v1::EmptyResponse>* ChunkStorage::Stub::PrepareAsyncRemoveReferenceRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minecpp::proto::service::chunk_storage::v1::EmptyResponse, ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_RemoveReference_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::chunk_storage::v1::EmptyResponse>* ChunkStorage::Stub::AsyncRemoveReferenceRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncRemoveReferenceRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ChunkStorage::Stub::HeightAt(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest& request, ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest, ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_HeightAt_, context, request, response);
}

void ChunkStorage::Stub::async::HeightAt(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest* request, ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest, ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_HeightAt_, context, request, response, std::move(f));
}

void ChunkStorage::Stub::async::HeightAt(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest* request, ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_HeightAt_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse>* ChunkStorage::Stub::PrepareAsyncHeightAtRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse, ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_HeightAt_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse>* ChunkStorage::Stub::AsyncHeightAtRaw(::grpc::ClientContext* context, const ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncHeightAtRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ChunkStorage::Stub::GetBlock(::grpc::ClientContext* context, const ::minecpp::proto::common::v1::BlockPosition& request, ::minecpp::proto::common::v1::BlockState* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minecpp::proto::common::v1::BlockPosition, ::minecpp::proto::common::v1::BlockState, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetBlock_, context, request, response);
}

void ChunkStorage::Stub::async::GetBlock(::grpc::ClientContext* context, const ::minecpp::proto::common::v1::BlockPosition* request, ::minecpp::proto::common::v1::BlockState* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minecpp::proto::common::v1::BlockPosition, ::minecpp::proto::common::v1::BlockState, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetBlock_, context, request, response, std::move(f));
}

void ChunkStorage::Stub::async::GetBlock(::grpc::ClientContext* context, const ::minecpp::proto::common::v1::BlockPosition* request, ::minecpp::proto::common::v1::BlockState* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetBlock_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::common::v1::BlockState>* ChunkStorage::Stub::PrepareAsyncGetBlockRaw(::grpc::ClientContext* context, const ::minecpp::proto::common::v1::BlockPosition& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minecpp::proto::common::v1::BlockState, ::minecpp::proto::common::v1::BlockPosition, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetBlock_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minecpp::proto::common::v1::BlockState>* ChunkStorage::Stub::AsyncGetBlockRaw(::grpc::ClientContext* context, const ::minecpp::proto::common::v1::BlockPosition& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetBlockRaw(context, request, cq);
  result->StartCall();
  return result;
}

ChunkStorage::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChunkStorage_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChunkStorage::Service, ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest, ::minecpp::proto::chunk::v1::Chunk, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChunkStorage::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest* req,
             ::minecpp::proto::chunk::v1::Chunk* resp) {
               return service->LoadChunk(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChunkStorage_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChunkStorage::Service, ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChunkStorage::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest* req,
             ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* resp) {
               return service->SetBlock(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChunkStorage_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChunkStorage::Service, ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest, ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChunkStorage::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest* req,
             ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse* resp) {
               return service->AddReferences(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChunkStorage_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChunkStorage::Service, ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChunkStorage::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest* req,
             ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* resp) {
               return service->RemoveReference(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChunkStorage_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChunkStorage::Service, ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest, ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChunkStorage::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest* req,
             ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse* resp) {
               return service->HeightAt(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChunkStorage_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChunkStorage::Service, ::minecpp::proto::common::v1::BlockPosition, ::minecpp::proto::common::v1::BlockState, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChunkStorage::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minecpp::proto::common::v1::BlockPosition* req,
             ::minecpp::proto::common::v1::BlockState* resp) {
               return service->GetBlock(ctx, req, resp);
             }, this)));
}

ChunkStorage::Service::~Service() {
}

::grpc::Status ChunkStorage::Service::LoadChunk(::grpc::ServerContext* context, const ::minecpp::proto::service::chunk_storage::v1::LoadChunkRequest* request, ::minecpp::proto::chunk::v1::Chunk* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChunkStorage::Service::SetBlock(::grpc::ServerContext* context, const ::minecpp::proto::service::chunk_storage::v1::SetBlockRequest* request, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChunkStorage::Service::AddReferences(::grpc::ServerContext* context, const ::minecpp::proto::service::chunk_storage::v1::AddReferencesRequest* request, ::minecpp::proto::service::chunk_storage::v1::AddReferencesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChunkStorage::Service::RemoveReference(::grpc::ServerContext* context, const ::minecpp::proto::service::chunk_storage::v1::RemoveReferencesRequest* request, ::minecpp::proto::service::chunk_storage::v1::EmptyResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChunkStorage::Service::HeightAt(::grpc::ServerContext* context, const ::minecpp::proto::service::chunk_storage::v1::HeightAtRequest* request, ::minecpp::proto::service::chunk_storage::v1::HeightAtResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChunkStorage::Service::GetBlock(::grpc::ServerContext* context, const ::minecpp::proto::common::v1::BlockPosition* request, ::minecpp::proto::common::v1::BlockState* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace minecpp
}  // namespace proto
}  // namespace service
}  // namespace chunk_storage
}  // namespace v1
