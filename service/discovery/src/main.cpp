#include "service.h"
#include <mb/core.h>
#include <spdlog/spdlog.h>

int main()
{
   auto host = mb::getenv("DISCOVERY_HOST").unwrap("0.0.0.0:9911");

   minecpp::service::discovery::Service service;
   grpc::ServerBuilder builder;
   builder.AddListeningPort(host, grpc::InsecureServerCredentials());
   builder.RegisterService(&service);
   std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

   spdlog::log(spdlog::level::info, "starting api server: {}", host);
   server->Wait();
}