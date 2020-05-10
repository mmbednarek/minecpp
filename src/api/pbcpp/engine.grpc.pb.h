// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: engine.proto
#ifndef GRPC_engine_2eproto__INCLUDED
#define GRPC_engine_2eproto__INCLUDED

#include "engine.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc_impl {
class CompletionQueue;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc_impl

namespace grpc {
namespace experimental {
template <typename RequestT, typename ResponseT>
class MessageAllocator;
}  // namespace experimental
}  // namespace grpc

namespace minecpp {
namespace engine {

class PlayerService final {
 public:
  static constexpr char const* service_full_name() {
    return "minecpp.engine.PlayerService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status AcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::minecpp::engine::AcceptPlayerResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::minecpp::engine::AcceptPlayerResponse>> AsyncAcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::minecpp::engine::AcceptPlayerResponse>>(AsyncAcceptPlayerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::minecpp::engine::AcceptPlayerResponse>> PrepareAsyncAcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::minecpp::engine::AcceptPlayerResponse>>(PrepareAsyncAcceptPlayerRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void AcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest* request, ::minecpp::engine::AcceptPlayerResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void AcceptPlayer(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::minecpp::engine::AcceptPlayerResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void AcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest* request, ::minecpp::engine::AcceptPlayerResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      virtual void AcceptPlayer(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::minecpp::engine::AcceptPlayerResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::minecpp::engine::AcceptPlayerResponse>* AsyncAcceptPlayerRaw(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::minecpp::engine::AcceptPlayerResponse>* PrepareAsyncAcceptPlayerRaw(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status AcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::minecpp::engine::AcceptPlayerResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::minecpp::engine::AcceptPlayerResponse>> AsyncAcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::minecpp::engine::AcceptPlayerResponse>>(AsyncAcceptPlayerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::minecpp::engine::AcceptPlayerResponse>> PrepareAsyncAcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::minecpp::engine::AcceptPlayerResponse>>(PrepareAsyncAcceptPlayerRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void AcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest* request, ::minecpp::engine::AcceptPlayerResponse* response, std::function<void(::grpc::Status)>) override;
      void AcceptPlayer(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::minecpp::engine::AcceptPlayerResponse* response, std::function<void(::grpc::Status)>) override;
      void AcceptPlayer(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest* request, ::minecpp::engine::AcceptPlayerResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      void AcceptPlayer(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::minecpp::engine::AcceptPlayerResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::minecpp::engine::AcceptPlayerResponse>* AsyncAcceptPlayerRaw(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::minecpp::engine::AcceptPlayerResponse>* PrepareAsyncAcceptPlayerRaw(::grpc::ClientContext* context, const ::minecpp::engine::AcceptPlayerRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_AcceptPlayer_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status AcceptPlayer(::grpc::ServerContext* context, const ::minecpp::engine::AcceptPlayerRequest* request, ::minecpp::engine::AcceptPlayerResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_AcceptPlayer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_AcceptPlayer() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_AcceptPlayer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AcceptPlayer(::grpc::ServerContext* /*context*/, const ::minecpp::engine::AcceptPlayerRequest* /*request*/, ::minecpp::engine::AcceptPlayerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAcceptPlayer(::grpc::ServerContext* context, ::minecpp::engine::AcceptPlayerRequest* request, ::grpc::ServerAsyncResponseWriter< ::minecpp::engine::AcceptPlayerResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_AcceptPlayer<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_AcceptPlayer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_AcceptPlayer() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc_impl::internal::CallbackUnaryHandler< ::minecpp::engine::AcceptPlayerRequest, ::minecpp::engine::AcceptPlayerResponse>(
          [this](::grpc::ServerContext* context,
                 const ::minecpp::engine::AcceptPlayerRequest* request,
                 ::minecpp::engine::AcceptPlayerResponse* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->AcceptPlayer(context, request, response, controller);
                 }));
    }
    void SetMessageAllocatorFor_AcceptPlayer(
        ::grpc::experimental::MessageAllocator< ::minecpp::engine::AcceptPlayerRequest, ::minecpp::engine::AcceptPlayerResponse>* allocator) {
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::minecpp::engine::AcceptPlayerRequest, ::minecpp::engine::AcceptPlayerResponse>*>(
          ::grpc::Service::experimental().GetHandler(0))
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_AcceptPlayer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AcceptPlayer(::grpc::ServerContext* /*context*/, const ::minecpp::engine::AcceptPlayerRequest* /*request*/, ::minecpp::engine::AcceptPlayerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void AcceptPlayer(::grpc::ServerContext* /*context*/, const ::minecpp::engine::AcceptPlayerRequest* /*request*/, ::minecpp::engine::AcceptPlayerResponse* /*response*/, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  typedef ExperimentalWithCallbackMethod_AcceptPlayer<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_AcceptPlayer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_AcceptPlayer() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_AcceptPlayer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AcceptPlayer(::grpc::ServerContext* /*context*/, const ::minecpp::engine::AcceptPlayerRequest* /*request*/, ::minecpp::engine::AcceptPlayerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_AcceptPlayer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_AcceptPlayer() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_AcceptPlayer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AcceptPlayer(::grpc::ServerContext* /*context*/, const ::minecpp::engine::AcceptPlayerRequest* /*request*/, ::minecpp::engine::AcceptPlayerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAcceptPlayer(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_AcceptPlayer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_AcceptPlayer() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc_impl::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->AcceptPlayer(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_AcceptPlayer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AcceptPlayer(::grpc::ServerContext* /*context*/, const ::minecpp::engine::AcceptPlayerRequest* /*request*/, ::minecpp::engine::AcceptPlayerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void AcceptPlayer(::grpc::ServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_AcceptPlayer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_AcceptPlayer() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::minecpp::engine::AcceptPlayerRequest, ::minecpp::engine::AcceptPlayerResponse>(std::bind(&WithStreamedUnaryMethod_AcceptPlayer<BaseClass>::StreamedAcceptPlayer, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_AcceptPlayer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status AcceptPlayer(::grpc::ServerContext* /*context*/, const ::minecpp::engine::AcceptPlayerRequest* /*request*/, ::minecpp::engine::AcceptPlayerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedAcceptPlayer(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::minecpp::engine::AcceptPlayerRequest,::minecpp::engine::AcceptPlayerResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_AcceptPlayer<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_AcceptPlayer<Service > StreamedService;
};

}  // namespace engine
}  // namespace minecpp


#endif  // GRPC_engine_2eproto__INCLUDED
