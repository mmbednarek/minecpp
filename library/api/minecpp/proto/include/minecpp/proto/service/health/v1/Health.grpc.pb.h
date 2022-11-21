// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: minecpp/proto/service/health/v1/Health.proto
#ifndef GRPC_minecpp_2fproto_2fservice_2fhealth_2fv1_2fHealth_2eproto__INCLUDED
#define GRPC_minecpp_2fproto_2fservice_2fhealth_2fv1_2fHealth_2eproto__INCLUDED

#include <minecpp/proto/service/health/v1/Health.pb.h>

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
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
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>

namespace minecpp { namespace proto { namespace Service { namespace health { namespace v1 {

class HealthService final
{
 public:
   static constexpr char const *service_full_name()
   {
      return "minecpp.proto.Service.health.v1.HealthService";
   }

   class StubInterface
   {
    public:
      virtual ~StubInterface() {}

      virtual ::grpc::Status
      GetServiceStatus(::grpc::ClientContext *context,
                       const ::minecpp::proto::Service::health::v1::Request &request,
                       ::minecpp::proto::Service::health::v1::ServiceStatus *response) = 0;

      std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::Service::health::v1::ServiceStatus>>
      AsyncGetServiceStatus(::grpc::ClientContext *context,
                            const ::minecpp::proto::Service::health::v1::Request &request,
                            ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
                 ::minecpp::proto::Service::health::v1::ServiceStatus>>(
                 AsyncGetServiceStatusRaw(context, request, cq));
      }

      std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
              ::minecpp::proto::Service::health::v1::ServiceStatus>>
      PrepareAsyncGetServiceStatus(::grpc::ClientContext *context,
                                   const ::minecpp::proto::Service::health::v1::Request &request,
                                   ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<
                 ::minecpp::proto::Service::health::v1::ServiceStatus>>(
                 PrepareAsyncGetServiceStatusRaw(context, request, cq));
      }

      class async_interface
      {
       public:
         virtual ~async_interface() {}

         virtual void GetServiceStatus(::grpc::ClientContext *context,
                                       const ::minecpp::proto::Service::health::v1::Request *request,
                                       ::minecpp::proto::Service::health::v1::ServiceStatus *response,
                                       std::function<void(::grpc::Status)>) = 0;
         virtual void GetServiceStatus(::grpc::ClientContext *context,
                                       const ::minecpp::proto::Service::health::v1::Request *request,
                                       ::minecpp::proto::Service::health::v1::ServiceStatus *response,
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
      virtual ::grpc::ClientAsyncResponseReaderInterface<::minecpp::proto::Service::health::v1::ServiceStatus>
              *AsyncGetServiceStatusRaw(::grpc::ClientContext *context,
                                        const ::minecpp::proto::Service::health::v1::Request &request,
                                        ::grpc::CompletionQueue *cq) = 0;
      virtual ::grpc::ClientAsyncResponseReaderInterface<::minecpp::proto::Service::health::v1::ServiceStatus>
              *PrepareAsyncGetServiceStatusRaw(::grpc::ClientContext *context,
                                               const ::minecpp::proto::Service::health::v1::Request &request,
                                               ::grpc::CompletionQueue *cq) = 0;
   };

   class Stub final : public StubInterface
   {
    public:
      Stub(const std::shared_ptr<::grpc::ChannelInterface> &channel,
           const ::grpc::StubOptions &options = ::grpc::StubOptions());
      ::grpc::Status
      GetServiceStatus(::grpc::ClientContext *context,
                       const ::minecpp::proto::Service::health::v1::Request &request,
                       ::minecpp::proto::Service::health::v1::ServiceStatus *response) override;

      std::unique_ptr<::grpc::ClientAsyncResponseReader<::minecpp::proto::Service::health::v1::ServiceStatus>>
      AsyncGetServiceStatus(::grpc::ClientContext *context,
                            const ::minecpp::proto::Service::health::v1::Request &request,
                            ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<
                 ::grpc::ClientAsyncResponseReader<::minecpp::proto::Service::health::v1::ServiceStatus>>(
                 AsyncGetServiceStatusRaw(context, request, cq));
      }

      std::unique_ptr<::grpc::ClientAsyncResponseReader<::minecpp::proto::Service::health::v1::ServiceStatus>>
      PrepareAsyncGetServiceStatus(::grpc::ClientContext *context,
                                   const ::minecpp::proto::Service::health::v1::Request &request,
                                   ::grpc::CompletionQueue *cq)
      {
         return std::unique_ptr<
                 ::grpc::ClientAsyncResponseReader<::minecpp::proto::Service::health::v1::ServiceStatus>>(
                 PrepareAsyncGetServiceStatusRaw(context, request, cq));
      }

      class async final : public StubInterface::async_interface
      {
       public:
         void GetServiceStatus(::grpc::ClientContext *context,
                               const ::minecpp::proto::Service::health::v1::Request *request,
                               ::minecpp::proto::Service::health::v1::ServiceStatus *response,
                               std::function<void(::grpc::Status)>) override;
         void GetServiceStatus(::grpc::ClientContext *context,
                               const ::minecpp::proto::Service::health::v1::Request *request,
                               ::minecpp::proto::Service::health::v1::ServiceStatus *response,
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

      ::grpc::ClientAsyncResponseReader<::minecpp::proto::Service::health::v1::ServiceStatus> *
      AsyncGetServiceStatusRaw(::grpc::ClientContext *context,
                               const ::minecpp::proto::Service::health::v1::Request &request,
                               ::grpc::CompletionQueue *cq) override;
      ::grpc::ClientAsyncResponseReader<::minecpp::proto::Service::health::v1::ServiceStatus> *
      PrepareAsyncGetServiceStatusRaw(::grpc::ClientContext *context,
                                      const ::minecpp::proto::Service::health::v1::Request &request,
                                      ::grpc::CompletionQueue *cq) override;
      const ::grpc::internal::RpcMethod rpcmethod_GetServiceStatus_;
   };

   static std::unique_ptr<Stub> NewStub(const std::shared_ptr<::grpc::ChannelInterface> &channel,
                                        const ::grpc::StubOptions &options = ::grpc::StubOptions());

   class Service : public ::grpc::Service
   {
    public:
      Service();
      virtual ~Service();
      virtual ::grpc::Status GetServiceStatus(::grpc::ServerContext *context,
                                              const ::minecpp::proto::Service::health::v1::Request *request,
                                              ::minecpp::proto::Service::health::v1::ServiceStatus *response);
   };

   template<class BaseClass>
   class WithAsyncMethod_GetServiceStatus : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithAsyncMethod_GetServiceStatus()
      {
         ::grpc::Service::MarkMethodAsync(0);
      }

      ~WithAsyncMethod_GetServiceStatus() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      GetServiceStatus(::grpc::ServerContext * /*context*/,
                       const ::minecpp::proto::Service::health::v1::Request * /*request*/,
                       ::minecpp::proto::Service::health::v1::ServiceStatus * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      void RequestGetServiceStatus(
              ::grpc::ServerContext *context, ::minecpp::proto::Service::health::v1::Request *request,
              ::grpc::ServerAsyncResponseWriter<::minecpp::proto::Service::health::v1::ServiceStatus>
                      *response,
              ::grpc::CompletionQueue *new_call_cq, ::grpc::ServerCompletionQueue *notification_cq, void *tag)
      {
         ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
      }
   };

   typedef WithAsyncMethod_GetServiceStatus<Service> AsyncService;

   template<class BaseClass>
   class WithCallbackMethod_GetServiceStatus : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithCallbackMethod_GetServiceStatus()
      {
         ::grpc::Service::MarkMethodCallback(
                 0, new ::grpc::internal::CallbackUnaryHandler<
                            ::minecpp::proto::Service::health::v1::Request,
                            ::minecpp::proto::Service::health::v1::ServiceStatus>(
                            [this](::grpc::CallbackServerContext *context,
                                   const ::minecpp::proto::Service::health::v1::Request *request,
                                   ::minecpp::proto::Service::health::v1::ServiceStatus *response) {
                               return this->GetServiceStatus(context, request, response);
                            }));
      }

      void SetMessageAllocatorFor_GetServiceStatus(
              ::grpc::MessageAllocator<::minecpp::proto::Service::health::v1::Request,
                                       ::minecpp::proto::Service::health::v1::ServiceStatus> *allocator)
      {
         ::grpc::internal::MethodHandler *const handler = ::grpc::Service::GetHandler(0);
         static_cast<::grpc::internal::CallbackUnaryHandler<
                 ::minecpp::proto::Service::health::v1::Request,
                 ::minecpp::proto::Service::health::v1::ServiceStatus> *>(handler)
                 ->SetMessageAllocator(allocator);
      }

      ~WithCallbackMethod_GetServiceStatus() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      GetServiceStatus(::grpc::ServerContext * /*context*/,
                       const ::minecpp::proto::Service::health::v1::Request * /*request*/,
                       ::minecpp::proto::Service::health::v1::ServiceStatus * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      virtual ::grpc::ServerUnaryReactor *
      GetServiceStatus(::grpc::CallbackServerContext * /*context*/,
                       const ::minecpp::proto::Service::health::v1::Request * /*request*/,
                       ::minecpp::proto::Service::health::v1::ServiceStatus * /*response*/)
      {
         return nullptr;
      }
   };

   typedef WithCallbackMethod_GetServiceStatus<Service> CallbackService;
   typedef CallbackService ExperimentalCallbackService;

   template<class BaseClass>
   class WithGenericMethod_GetServiceStatus : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithGenericMethod_GetServiceStatus()
      {
         ::grpc::Service::MarkMethodGeneric(0);
      }

      ~WithGenericMethod_GetServiceStatus() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      GetServiceStatus(::grpc::ServerContext * /*context*/,
                       const ::minecpp::proto::Service::health::v1::Request * /*request*/,
                       ::minecpp::proto::Service::health::v1::ServiceStatus * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }
   };

   template<class BaseClass>
   class WithRawMethod_GetServiceStatus : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithRawMethod_GetServiceStatus()
      {
         ::grpc::Service::MarkMethodRaw(0);
      }

      ~WithRawMethod_GetServiceStatus() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      GetServiceStatus(::grpc::ServerContext * /*context*/,
                       const ::minecpp::proto::Service::health::v1::Request * /*request*/,
                       ::minecpp::proto::Service::health::v1::ServiceStatus * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      void RequestGetServiceStatus(::grpc::ServerContext *context, ::grpc::ByteBuffer *request,
                                   ::grpc::ServerAsyncResponseWriter<::grpc::ByteBuffer> *response,
                                   ::grpc::CompletionQueue *new_call_cq,
                                   ::grpc::ServerCompletionQueue *notification_cq, void *tag)
      {
         ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
      }
   };

   template<class BaseClass>
   class WithRawCallbackMethod_GetServiceStatus : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithRawCallbackMethod_GetServiceStatus()
      {
         ::grpc::Service::MarkMethodRawCallback(
                 0, new ::grpc::internal::CallbackUnaryHandler<::grpc::ByteBuffer, ::grpc::ByteBuffer>(
                            [this](::grpc::CallbackServerContext *context, const ::grpc::ByteBuffer *request,
                                   ::grpc::ByteBuffer *response) {
                               return this->GetServiceStatus(context, request, response);
                            }));
      }

      ~WithRawCallbackMethod_GetServiceStatus() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable synchronous version of this method
      ::grpc::Status
      GetServiceStatus(::grpc::ServerContext * /*context*/,
                       const ::minecpp::proto::Service::health::v1::Request * /*request*/,
                       ::minecpp::proto::Service::health::v1::ServiceStatus * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      virtual ::grpc::ServerUnaryReactor *GetServiceStatus(::grpc::CallbackServerContext * /*context*/,
                                                           const ::grpc::ByteBuffer * /*request*/,
                                                           ::grpc::ByteBuffer * /*response*/)
      {
         return nullptr;
      }
   };

   template<class BaseClass>
   class WithStreamedUnaryMethod_GetServiceStatus : public BaseClass
   {
    private:
      void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

    public:
      WithStreamedUnaryMethod_GetServiceStatus()
      {
         ::grpc::Service::MarkMethodStreamed(
                 0, new ::grpc::internal::StreamedUnaryHandler<
                            ::minecpp::proto::Service::health::v1::Request,
                            ::minecpp::proto::Service::health::v1::ServiceStatus>(
                            [this](::grpc::ServerContext *context,
                                   ::grpc::ServerUnaryStreamer<
                                           ::minecpp::proto::Service::health::v1::Request,
                                           ::minecpp::proto::Service::health::v1::ServiceStatus> *streamer) {
                               return this->StreamedGetServiceStatus(context, streamer);
                            }));
      }

      ~WithStreamedUnaryMethod_GetServiceStatus() override
      {
         BaseClassMustBeDerivedFromService(this);
      }

      // disable regular version of this method
      ::grpc::Status
      GetServiceStatus(::grpc::ServerContext * /*context*/,
                       const ::minecpp::proto::Service::health::v1::Request * /*request*/,
                       ::minecpp::proto::Service::health::v1::ServiceStatus * /*response*/) override
      {
         abort();
         return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
      }

      // replace default version of method with streamed unary
      virtual ::grpc::Status StreamedGetServiceStatus(
              ::grpc::ServerContext *context,
              ::grpc::ServerUnaryStreamer<::minecpp::proto::Service::health::v1::Request,
                                          ::minecpp::proto::Service::health::v1::ServiceStatus>
                      *server_unary_streamer) = 0;
   };

   typedef WithStreamedUnaryMethod_GetServiceStatus<Service> StreamedUnaryService;
   typedef Service SplitStreamedService;
   typedef WithStreamedUnaryMethod_GetServiceStatus<Service> StreamedService;
};

}}}}}// namespace minecpp::proto::Service::health::v1


#endif// GRPC_minecpp_2fproto_2fservice_2fhealth_2fv1_2fHealth_2eproto__INCLUDED
