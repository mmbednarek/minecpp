#include "service.h"
#include <grpcpp/server_builder.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <mineutils/string.h>

auto main() -> int {
   std::string str = "";
   spdlog::info("hash of {} is {}", str, Utils::hash_string(str));

   auto region_path = std::getenv("REGION_PATH");
   if (!region_path) {
      spdlog::error("REGION_PATH variable required\n");
      return 1;
   }

   std::string listen = std::getenv("LISTEN");
   if (listen.empty()) {
      listen = "0.0.0.0:7000";
   }

   Service s(region_path);

   grpc::ServerBuilder builder;
   builder.AddListeningPort(listen, grpc::InsecureServerCredentials());
   builder.RegisterService(&s);

   std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
   spdlog::info("starting grpc server on address {}", listen);
   server->Wait();
}
