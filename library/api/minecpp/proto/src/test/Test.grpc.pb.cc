// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: minecpp/proto/test/Test.proto

#include <minecpp/proto/test/Test.pb.h>
#include <minecpp/proto/test/Test.grpc.pb.h>

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
namespace test {

static const char* TestService_method_names[] = {
  "/minecpp.proto.test.TestService/StartStream",
};

std::unique_ptr< TestService::Stub> TestService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< TestService::Stub> stub(new TestService::Stub(channel, options));
  return stub;
}

TestService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_StartStream_(TestService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::minecpp::proto::test::TestMessage, ::minecpp::proto::test::TestMessage>* TestService::Stub::StartStreamRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::minecpp::proto::test::TestMessage, ::minecpp::proto::test::TestMessage>::Create(channel_.get(), rpcmethod_StartStream_, context);
}

void TestService::Stub::async::StartStream(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::minecpp::proto::test::TestMessage,::minecpp::proto::test::TestMessage>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::minecpp::proto::test::TestMessage,::minecpp::proto::test::TestMessage>::Create(stub_->channel_.get(), stub_->rpcmethod_StartStream_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::minecpp::proto::test::TestMessage, ::minecpp::proto::test::TestMessage>* TestService::Stub::AsyncStartStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::minecpp::proto::test::TestMessage, ::minecpp::proto::test::TestMessage>::Create(channel_.get(), cq, rpcmethod_StartStream_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::minecpp::proto::test::TestMessage, ::minecpp::proto::test::TestMessage>* TestService::Stub::PrepareAsyncStartStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::minecpp::proto::test::TestMessage, ::minecpp::proto::test::TestMessage>::Create(channel_.get(), cq, rpcmethod_StartStream_, context, false, nullptr);
}

TestService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TestService_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< TestService::Service, ::minecpp::proto::test::TestMessage, ::minecpp::proto::test::TestMessage>(
          [](TestService::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::minecpp::proto::test::TestMessage,
             ::minecpp::proto::test::TestMessage>* stream) {
               return service->StartStream(ctx, stream);
             }, this)));
}

TestService::Service::~Service() {
}

::grpc::Status TestService::Service::StartStream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::minecpp::proto::test::TestMessage, ::minecpp::proto::test::TestMessage>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace minecpp
}  // namespace proto
}  // namespace test

