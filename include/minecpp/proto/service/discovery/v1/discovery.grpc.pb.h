// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: minecpp/proto/service/discovery/v1/discovery.proto
#ifndef GRPC_minecpp_2fproto_2fservice_2fdiscovery_2fv1_2fdiscovery_2eproto__INCLUDED
#define GRPC_minecpp_2fproto_2fservice_2fdiscovery_2fv1_2fdiscovery_2eproto__INCLUDED

#include <minecpp/proto/service/discovery/v1/discovery.pb.h>

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace minecpp { namespace proto { namespace service { namespace discovery { namespace v1 {

class DiscoveryService final
{
 public:
   static constexpr char const *service_full_name()
   {
      return "minecpp.proto.service.discovery.v1.DiscoveryService";
   }

   class StubInterface
   {
    public:
      virtual ~StubInterface() {}

      virtual ::grpc::Status
      Resolve(::grpc::ClientContext *context,
              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response) = 0;

      std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse>>
      AsyncResolve(::grpc::ClientContext *context,
                   const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
                   ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
                 ::minecpp::proto::service::discovery::v1::DiscoveryResponse>>(
                 AsyncResolveRaw(context, request, cq));
      }

      std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse>>
      PrepareAsyncResolve(::grpc::ClientContext *context,
                          const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
                          ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
                 ::minecpp::proto::service::discovery::v1::DiscoveryResponse>>(
                 PrepareAsyncResolveRaw(context, request, cq));
      }

      virtual ::grpc::Status
      RegisterService(::grpc::ClientContext *context,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                      ::minecpp::proto::service::discovery::v1::EmptyResult *response) = 0;

      std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::service::discovery::v1::EmptyResult>>
      AsyncRegisterService(::grpc::ClientContext *context,
                           const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                           ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
                 ::minecpp::proto::service::discovery::v1::EmptyResult>>(
                 AsyncRegisterServiceRaw(context, request, cq));
      }

      std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::service::discovery::v1::EmptyResult>>
      PrepareAsyncRegisterService(::grpc::ClientContext *context,
                                  const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                                  ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
                 ::minecpp::proto::service::discovery::v1::EmptyResult>>(
                 PrepareAsyncRegisterServiceRaw(context, request, cq));
      }

      class async_interface
      {
       public:
         virtual ~async_interface() {}

         virtual void Resolve(::grpc::ClientContext *context,
                              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest *request,
                              ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response,
                              std::function<void(::grpc::Status)>) = 0;
         virtual void Resolve(::grpc::ClientContext *context,
                              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest *request,
                              ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response,
                              ::grpc::ClientUnaryReactor *reactor) = 0;
         virtual void
         RegisterService(::grpc::ClientContext *context,
                         const ::minecpp::proto::service::discovery::v1::RegisterRequest *request,
                         ::minecpp::proto::service::discovery::v1::EmptyResult *response,
                         std::function<void(::grpc::Status)>) = 0;
         virtual void
         RegisterService(::grpc::ClientContext *context,
                         const ::minecpp::proto::service::discovery::v1::RegisterRequest *request,
                         ::minecpp::proto::service::discovery::v1::EmptyResult *response,
                         ::grpc::ClientUnaryReactor *reactor) = 0;
      };
      typedef class async_interface experimental_async_interface;

      virtual class async_interface *async()
      {
         return nullptr;
      }

      class async_interface *experimental_async()
      {
         return async();
      }

    private:
      virtual ::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse> *
      AsyncResolveRaw(::grpc::ClientContext *context,
                      const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
                      ::grpc::CompletionQueue *cq) = 0;
      virtual ::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse> *
      PrepareAsyncResolveRaw(::grpc::ClientContext *context,
                             const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
                             ::grpc::CompletionQueue *cq) = 0;
      virtual ::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::service::discovery::v1::EmptyResult> *
      AsyncRegisterServiceRaw(::grpc::ClientContext *context,
                              const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                              ::grpc::CompletionQueue *cq) = 0;
      virtual ::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::service::discovery::v1::EmptyResult> *
      PrepareAsyncRegisterServiceRaw(::grpc::ClientContext *context,
                                     const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                                     ::grpc::CompletionQueue *cq) = 0;
   };

   class Stub final : public StubInterface
   {
    public:
      Stub(const std::shared_ptr<::grpc::ChannelInterface> &channel,
           const ::grpc::StubOptions &options = ::grpc::StubOptions());
      ::grpc::Status Resolve(::grpc::ClientContext *context,
                             const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
                             ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response) override;

      std::unique_ptr<
              ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::DiscoveryResponse>>
      AsyncResolve(::grpc::ClientContext *context,
                   const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
                   ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<::grpc::ClientAsyncResponseReader<
                 ::minecpp::proto::service::discovery::v1::DiscoveryResponse>>(
                 AsyncResolveRaw(context, request, cq));
      }

      std::unique_ptr<
              ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::DiscoveryResponse>>
      PrepareAsyncResolve(::grpc::ClientContext *context,
                          const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
                          ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<::grpc::ClientAsyncResponseReader<
                 ::minecpp::proto::service::discovery::v1::DiscoveryResponse>>(
                 PrepareAsyncResolveRaw(context, request, cq));
      }

      ::grpc::Status
      RegisterService(::grpc::ClientContext *context,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                      ::minecpp::proto::service::discovery::v1::EmptyResult *response) override;

      std::unique_ptr<
              ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::EmptyResult>>
      AsyncRegisterService(::grpc::ClientContext *context,
                           const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                           ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<
                 ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::EmptyResult>>(
                 AsyncRegisterServiceRaw(context, request, cq));
      }

      std::unique_ptr<
              ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::EmptyResult>>
      PrepareAsyncRegisterService(::grpc::ClientContext *context,
                                  const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                                  ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<
                 ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::EmptyResult>>(
                 PrepareAsyncRegisterServiceRaw(context, request, cq));
      }

      class async final : public StubInterface::async_interface
      {
       public:
         void Resolve(::grpc::ClientContext *context,
                      const ::minecpp::proto::service::discovery::v1::DiscoveryRequest *request,
                      ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response,
                      std::function<void(::grpc::Status)>) override;
         void Resolve(::grpc::ClientContext *context,
                      const ::minecpp::proto::service::discovery::v1::DiscoveryRequest *request,
                      ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response,
                      ::grpc::ClientUnaryReactor *reactor) override;
         void RegisterService(::grpc::ClientContext *context,
                              const ::minecpp::proto::service::discovery::v1::RegisterRequest *request,
                              ::minecpp::proto::service::discovery::v1::EmptyResult *response,
                              std::function<void(::grpc::Status)>) override;
         void RegisterService(::grpc::ClientContext *context,
                              const ::minecpp::proto::service::discovery::v1::RegisterRequest *request,
                              ::minecpp::proto::service::discovery::v1::EmptyResult *response,
                              ::grpc::ClientUnaryReactor *reactor) override;

       private:
         friend class Stub;

         explicit async(Stub *stub) :
             stub_(stub)
         {
         }

         Stub *stub()
         {
            return stub_;
         }

         Stub *stub_;
      };

      class async *async() override
      {
         return &async_stub_;
      }

    private:
      std::shared_ptr<::grpc::ChannelInterface> channel_;

      class async async_stub_
      {
         this
      };

      ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::DiscoveryResponse> *
      AsyncResolveRaw(::grpc::ClientContext *context,
                      const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
                      ::grpc::CompletionQueue *cq) override;
      ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::DiscoveryResponse> *
      PrepareAsyncResolveRaw(::grpc::ClientContext *context,
                             const ::minecpp::proto::service::discovery::v1::DiscoveryRequest &request,
                             ::grpc::CompletionQueue *cq) override;
      ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::EmptyResult> *
      AsyncRegisterServiceRaw(::grpc::ClientContext *context,
                              const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                              ::grpc::CompletionQueue *cq) override;
      ::grpc::ClientAsyncResponseReader<::minecpp::proto::service::discovery::v1::EmptyResult> *
      PrepareAsyncRegisterServiceRaw(::grpc::ClientContext *context,
                                     const ::minecpp::proto::service::discovery::v1::RegisterRequest &request,
                                     ::grpc::CompletionQueue *cq) override;
      const ::grpc::internal::RpcMethod rpcmethod_Resolve_;
      const ::grpc::internal::RpcMethod rpcmethod_RegisterService_;
   };

   static std::unique_ptr<Stub> NewStub(const std::shared_ptr<::grpc::ChannelInterface> &channel,
                                        const ::grpc::StubOptions &options = ::grpc::StubOptions());

   class Service : public ::grpc::Service
   {
    public:
      Service();
      virtual ~Service();
      virtual ::grpc::Status
      Resolve(::grpc::ServerContext *context,
              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest *request,
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response);
      virtual ::grpc::Status
      RegisterService(::grpc::ServerContext *context,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest *request,
                      ::minecpp::proto::service::discovery::v1::EmptyResult *response);
   };

   template<class BaseClass>
   class WithAsyncMethod_Resolve : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithAsyncMethod_Resolve()
      {
         ::grpc::Service::MarkMethodAsync(0);
      }

      ~WithAsyncMethod_Resolve() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      Resolve(::grpc::ServerContext * /*context*/,
              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest * /*request*/,
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      void RequestResolve(
              ::grpc::ServerContext *context,
              ::minecpp::proto::service::discovery::v1::DiscoveryRequest *request,
              ::grpc::ServerAsyncResponseWriter<::minecpp::proto::service::discovery::v1::DiscoveryResponse>
                      *response,
              ::grpc::CompletionQueue *new_call_cq, ::grpc::ServerCompletionQueue *notification_cq, void *tag)
      {
         ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
      }
   };

   template<class BaseClass>
   class WithAsyncMethod_RegisterService : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithAsyncMethod_RegisterService()
      {
         ::grpc::Service::MarkMethodAsync(1);
      }

      ~WithAsyncMethod_RegisterService() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      RegisterService(::grpc::ServerContext * /*context*/,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest * /*request*/,
                      ::minecpp::proto::service::discovery::v1::EmptyResult * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      void RequestRegisterService(
              ::grpc::ServerContext *context,
              ::minecpp::proto::service::discovery::v1::RegisterRequest *request,
              ::grpc::ServerAsyncResponseWriter<::minecpp::proto::service::discovery::v1::EmptyResult>
                      *response,
              ::grpc::CompletionQueue *new_call_cq, ::grpc::ServerCompletionQueue *notification_cq, void *tag)
      {
         ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
      }
   };

   typedef WithAsyncMethod_Resolve<WithAsyncMethod_RegisterService<Service>> AsyncService;

   template<class BaseClass>
   class WithCallbackMethod_Resolve : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithCallbackMethod_Resolve()
      {
         ::grpc::Service::MarkMethodCallback(
                 0, new ::grpc::internal::CallbackUnaryHandler<
                            ::minecpp::proto::service::discovery::v1::DiscoveryRequest,
                            ::minecpp::proto::service::discovery::v1::DiscoveryResponse>(
                            [this](::grpc::CallbackServerContext *context,
                                   const ::minecpp::proto::service::discovery::v1::DiscoveryRequest *request,
                                   ::minecpp::proto::service::discovery::v1::DiscoveryResponse *response) {
                               return this->Resolve(context, request, response);
                            }));
      }

      void SetMessageAllocatorFor_Resolve(
              ::grpc::MessageAllocator<::minecpp::proto::service::discovery::v1::DiscoveryRequest,
                                       ::minecpp::proto::service::discovery::v1::DiscoveryResponse>
                      *allocator)
      {
         ::grpc::internal::MethodHandler *const handler = ::grpc::Service::GetHandler(0);
         static_cast<::grpc::internal::CallbackUnaryHandler<
                 ::minecpp::proto::service::discovery::v1::DiscoveryRequest,
                 ::minecpp::proto::service::discovery::v1::DiscoveryResponse> *>(handler)
                 ->SetMessageAllocator(allocator);
      }

      ~WithCallbackMethod_Resolve() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      Resolve(::grpc::ServerContext * /*context*/,
              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest * /*request*/,
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      virtual ::grpc::ServerUnaryReactor *
      Resolve(::grpc::CallbackServerContext * /*context*/,
              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest * /*request*/,
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse * /*response*/)
      {
         return nullptr;
      }
   };

   template<class BaseClass>
   class WithCallbackMethod_RegisterService : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithCallbackMethod_RegisterService()
      {
         ::grpc::Service::MarkMethodCallback(
                 1, new ::grpc::internal::CallbackUnaryHandler<
                            ::minecpp::proto::service::discovery::v1::RegisterRequest,
                            ::minecpp::proto::service::discovery::v1::EmptyResult>(
                            [this](::grpc::CallbackServerContext *context,
                                   const ::minecpp::proto::service::discovery::v1::RegisterRequest *request,
                                   ::minecpp::proto::service::discovery::v1::EmptyResult *response) {
                               return this->RegisterService(context, request, response);
                            }));
      }

      void SetMessageAllocatorFor_RegisterService(
              ::grpc::MessageAllocator<::minecpp::proto::service::discovery::v1::RegisterRequest,
                                       ::minecpp::proto::service::discovery::v1::EmptyResult> *allocator)
      {
         ::grpc::internal::MethodHandler *const handler = ::grpc::Service::GetHandler(1);
         static_cast<::grpc::internal::CallbackUnaryHandler<
                 ::minecpp::proto::service::discovery::v1::RegisterRequest,
                 ::minecpp::proto::service::discovery::v1::EmptyResult> *>(handler)
                 ->SetMessageAllocator(allocator);
      }

      ~WithCallbackMethod_RegisterService() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      RegisterService(::grpc::ServerContext * /*context*/,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest * /*request*/,
                      ::minecpp::proto::service::discovery::v1::EmptyResult * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      virtual ::grpc::ServerUnaryReactor *
      RegisterService(::grpc::CallbackServerContext * /*context*/,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest * /*request*/,
                      ::minecpp::proto::service::discovery::v1::EmptyResult * /*response*/)
      {
         return nullptr;
      }
   };

   typedef WithCallbackMethod_Resolve<WithCallbackMethod_RegisterService<Service>> CallbackService;
   typedef CallbackService ExperimentalCallbackService;

   template<class BaseClass>
   class WithGenericMethod_Resolve : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithGenericMethod_Resolve()
      {
         ::grpc::Service::MarkMethodGeneric(0);
      }

      ~WithGenericMethod_Resolve() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      Resolve(::grpc::ServerContext * /*context*/,
              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest * /*request*/,
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }
   };

   template<class BaseClass>
   class WithGenericMethod_RegisterService : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithGenericMethod_RegisterService()
      {
         ::grpc::Service::MarkMethodGeneric(1);
      }

      ~WithGenericMethod_RegisterService() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      RegisterService(::grpc::ServerContext * /*context*/,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest * /*request*/,
                      ::minecpp::proto::service::discovery::v1::EmptyResult * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }
   };

   template<class BaseClass>
   class WithRawMethod_Resolve : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithRawMethod_Resolve()
      {
         ::grpc::Service::MarkMethodRaw(0);
      }

      ~WithRawMethod_Resolve() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      Resolve(::grpc::ServerContext * /*context*/,
              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest * /*request*/,
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      void RequestResolve(::grpc::ServerContext *context, ::grpc::ByteBuffer *request,
                          ::grpc::ServerAsyncResponseWriter<::grpc::ByteBuffer> *response,
                          ::grpc::CompletionQueue *new_call_cq,
                          ::grpc::ServerCompletionQueue *notification_cq, void *tag)
      {
         ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
      }
   };

   template<class BaseClass>
   class WithRawMethod_RegisterService : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithRawMethod_RegisterService()
      {
         ::grpc::Service::MarkMethodRaw(1);
      }

      ~WithRawMethod_RegisterService() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      RegisterService(::grpc::ServerContext * /*context*/,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest * /*request*/,
                      ::minecpp::proto::service::discovery::v1::EmptyResult * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      void RequestRegisterService(::grpc::ServerContext *context, ::grpc::ByteBuffer *request,
                                  ::grpc::ServerAsyncResponseWriter<::grpc::ByteBuffer> *response,
                                  ::grpc::CompletionQueue *new_call_cq,
                                  ::grpc::ServerCompletionQueue *notification_cq, void *tag)
      {
         ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
      }
   };

   template<class BaseClass>
   class WithRawCallbackMethod_Resolve : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithRawCallbackMethod_Resolve()
      {
         ::grpc::Service::MarkMethodRawCallback(
                 0, new ::grpc::internal::CallbackUnaryHandler<::grpc::ByteBuffer, ::grpc::ByteBuffer>(
                            [this](::grpc::CallbackServerContext *context, const ::grpc::ByteBuffer *request,
                                   ::grpc::ByteBuffer *response) {
                               return this->Resolve(context, request, response);
                            }));
      }

      ~WithRawCallbackMethod_Resolve() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      Resolve(::grpc::ServerContext * /*context*/,
              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest * /*request*/,
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      virtual ::grpc::ServerUnaryReactor *Resolve(::grpc::CallbackServerContext * /*context*/,
                                                  const ::grpc::ByteBuffer * /*request*/,
                                                  ::grpc::ByteBuffer * /*response*/)
      {
         return nullptr;
      }
   };

   template<class BaseClass>
   class WithRawCallbackMethod_RegisterService : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithRawCallbackMethod_RegisterService()
      {
         ::grpc::Service::MarkMethodRawCallback(
                 1, new ::grpc::internal::CallbackUnaryHandler<::grpc::ByteBuffer, ::grpc::ByteBuffer>(
                            [this](::grpc::CallbackServerContext *context, const ::grpc::ByteBuffer *request,
                                   ::grpc::ByteBuffer *response) {
                               return this->RegisterService(context, request, response);
                            }));
      }

      ~WithRawCallbackMethod_RegisterService() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      RegisterService(::grpc::ServerContext * /*context*/,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest * /*request*/,
                      ::minecpp::proto::service::discovery::v1::EmptyResult * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      virtual ::grpc::ServerUnaryReactor *RegisterService(::grpc::CallbackServerContext * /*context*/,
                                                          const ::grpc::ByteBuffer * /*request*/,
                                                          ::grpc::ByteBuffer * /*response*/)
      {
         return nullptr;
      }
   };

   template<class BaseClass>
   class WithStreamedUnaryMethod_Resolve : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithStreamedUnaryMethod_Resolve()
      {
         ::grpc::Service::MarkMethodStreamed(
                 0, new ::grpc::internal::StreamedUnaryHandler<
                            ::minecpp::proto::service::discovery::v1::DiscoveryRequest,
                            ::minecpp::proto::service::discovery::v1::DiscoveryResponse>(
                            [this](::grpc::ServerContext *context,
                                   ::grpc::ServerUnaryStreamer<
                                           ::minecpp::proto::service::discovery::v1::DiscoveryRequest,
                                           ::minecpp::proto::service::discovery::v1::DiscoveryResponse>
                                           *streamer) { return this->StreamedResolve(context, streamer); }));
      }

      ~WithStreamedUnaryMethod_Resolve() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable regular version of this method
      ::grpc::Status
      Resolve(::grpc::ServerContext * /*context*/,
              const ::minecpp::proto::service::discovery::v1::DiscoveryRequest * /*request*/,
              ::minecpp::proto::service::discovery::v1::DiscoveryResponse * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      // replace default version of method with streamed unary
      virtual ::grpc::Status
      StreamedResolve(::grpc::ServerContext *context,
                      ::grpc::ServerUnaryStreamer<::minecpp::proto::service::discovery::v1::DiscoveryRequest,
                                                  ::minecpp::proto::service::discovery::v1::DiscoveryResponse>
                              *server_unary_streamer) = 0;
   };

   template<class BaseClass>
   class WithStreamedUnaryMethod_RegisterService : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithStreamedUnaryMethod_RegisterService()
      {
         ::grpc::Service::MarkMethodStreamed(
                 1, new ::grpc::internal::StreamedUnaryHandler<
                            ::minecpp::proto::service::discovery::v1::RegisterRequest,
                            ::minecpp::proto::service::discovery::v1::EmptyResult>(
                            [this](::grpc::ServerContext *context,
                                   ::grpc::ServerUnaryStreamer<
                                           ::minecpp::proto::service::discovery::v1::RegisterRequest,
                                           ::minecpp::proto::service::discovery::v1::EmptyResult> *streamer) {
                               return this->StreamedRegisterService(context, streamer);
                            }));
      }

      ~WithStreamedUnaryMethod_RegisterService() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable regular version of this method
      ::grpc::Status
      RegisterService(::grpc::ServerContext * /*context*/,
                      const ::minecpp::proto::service::discovery::v1::RegisterRequest * /*request*/,
                      ::minecpp::proto::service::discovery::v1::EmptyResult * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      // replace default version of method with streamed unary
      virtual ::grpc::Status StreamedRegisterService(
              ::grpc::ServerContext *context,
              ::grpc::ServerUnaryStreamer<::minecpp::proto::service::discovery::v1::RegisterRequest,
                                          ::minecpp::proto::service::discovery::v1::EmptyResult>
                      *server_unary_streamer) = 0;
   };

   typedef WithStreamedUnaryMethod_Resolve<WithStreamedUnaryMethod_RegisterService<Service>>
           StreamedUnaryService;
   typedef Service SplitStreamedService;
   typedef WithStreamedUnaryMethod_Resolve<WithStreamedUnaryMethod_RegisterService<Service>> StreamedService;
};

}}}}}// namespace minecpp::proto::service::discovery::v1


#endif// GRPC_minecpp_2fproto_2fservice_2fdiscovery_2fv1_2fdiscovery_2eproto__INCLUDED
