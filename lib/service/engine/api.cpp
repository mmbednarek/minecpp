#include <minecpp/service/engine/api.h>

namespace minecpp::service::engine {

Client::Client(std::shared_ptr<grpc::ChannelInterface> channel, std::unique_ptr<proto::service::engine::v1::EngineService::Stub> stub) : m_channel(std::move(channel)),
                                                                                                                                         m_stub(std::move(stub)) {}

mb::result<Client> Client::create(std::string_view address) {
   auto channel = grpc::CreateChannel(std::string(address), grpc::InsecureChannelCredentials());
   auto stub = proto::service::engine::v1::EngineService::NewStub(channel);
   return Client(std::move(channel), std::move(stub));
}

}// namespace minecpp::service::engine