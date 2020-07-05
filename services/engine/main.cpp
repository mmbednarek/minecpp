#include "entities.h"
#include "players.h"
#include "service.h"
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/server_builder.h>
#include <iostream>
#include <spdlog/spdlog.h>

auto main() -> int {
   auto player_path = std::getenv("PLAYERS_PATH");
   if (!player_path) {
      spdlog::error("empty PLAYERS_PATH");
      return 1;
   }

   std::string chunk_storage_address = std::getenv("CHUNK_STORAGE_ADDRESS");
   if (chunk_storage_address.empty()) {
      spdlog::error("empty CHUNK_STORAGE_ADDRESS");
      return 1;
   }

   auto listen = std::getenv("LISTEN");
   if (!listen) {
      spdlog::error("empty LISTEN env");
      return 1;
   }

   Engine::EntityManager entities;
   Engine::PlayerManager players(player_path, entities);

   auto channel = grpc::CreateChannel(chunk_storage_address,
                                      grpc::InsecureChannelCredentials());
   std::shared_ptr<minecpp::chunk_storage::ChunkStorage::Stub> chunk_storage =
       minecpp::chunk_storage::ChunkStorage::NewStub(channel);

   Engine::Service service(entities, players, chunk_storage);

   grpc::ServerBuilder builder;
   builder.AddListeningPort(listen, grpc::InsecureServerCredentials());
   builder.RegisterService(&service);

   std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
   spdlog::info("starting grpc server on address {}", listen);
   server->Wait();
}