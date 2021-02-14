#include "entities.h"
#include "players.h"
#include "service.h"
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/server_builder.h>
#include <iostream>
#include <mb/core.h>
#include <spdlog/spdlog.h>

auto main() -> int {
   auto player_path = mb::getenv("PLAYERS_PATH").unwrap("world/playerdata");
   auto chunk_storage_address = mb::getenv("CHUNK_STORAGE_ADDRESS").unwrap("127.0.0.1:7000");
   auto listen = mb::getenv("LISTEN").unwrap("0.0.0.0:7800");

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