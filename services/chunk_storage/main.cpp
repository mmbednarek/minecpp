#include "service.h"
#include <game/level/level.h>
#include <game/blocks/state.h>
#include <grpcpp/server_builder.h>
#include <iostream>

auto main() -> int {
   std::cout << "enum states: " << Game::Block::Prop::Facing.num_states() << '\n';

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
   std::cerr << "grpc server started";
   server->Wait();
}
