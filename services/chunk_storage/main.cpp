#include "service.h"
#include <boost/log/trivial.hpp>
#include <game/level/level.h>
#include <grpcpp/server_builder.h>
#include <iostream>

auto main() -> int {
   auto region_path = std::getenv("REGION_PATH");
   if (!region_path) {
      std::cerr << "REGION_PATH variable required\n";
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
   BOOST_LOG_TRIVIAL(info) << "starting GRPC server";
   server->Wait();
}
