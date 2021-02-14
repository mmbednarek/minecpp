#include "service.h"
#include <grpcpp/server_builder.h>
#include <mb/core.h>
#include <spdlog/spdlog.h>

auto main() -> int {
   auto region_path = mb::getenv("REGION_PATH").unwrap("world/region");
   auto listen = mb::getenv("LISTEN").unwrap("0.0.0.0:7600");

   ChunkStorage::Service service(region_path);

   grpc::ServerBuilder builder;
   builder.AddListeningPort(listen, grpc::InsecureServerCredentials());
   builder.RegisterService(&service);

   std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
   spdlog::info("starting grpc server on address {}", listen);
   server->Wait();
}
