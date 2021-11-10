#include "api.h"
#include "dispatcher.h"
#include "entities.h"
#include "event_handler.h"
#include "players.h"
#include "world.h"
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/server_builder.h>
#include <iostream>
#include <mb/core.h>
#include <minecpp/proto/service/chunk_storage/v1/chunk_storage.grpc.pb.h>
#include <spdlog/spdlog.h>
#include <thread>

auto main() -> int {
   using namespace minecpp::service::engine;

   auto player_path = mb::getenv("PLAYERS_PATH").unwrap("world/playerdata");
   auto chunk_storage_address = mb::getenv("CHUNK_STORAGE_ADDRESS").unwrap("127.0.0.1:7000");
   auto listen = mb::getenv("LISTEN").unwrap("0.0.0.0:7800");

   EntityManager entities;
   PlayerManager players(player_path, entities);

   auto channel = grpc::CreateChannel(chunk_storage_address,
                                      grpc::InsecureChannelCredentials());
   auto chunk_storage = minecpp::proto::service::chunk_storage::v1::ChunkStorage::ChunkStorage::NewStub(channel);

   EventManager manager;
   Dispatcher dispatcher(manager);
   World world(boost::uuids::uuid(), *chunk_storage, dispatcher);

   EventHandler handler(dispatcher, players, entities, world);

   ApiImpl service(handler, manager);

   grpc::ServerBuilder builder;
   builder.AddListeningPort(listen, grpc::InsecureServerCredentials());
   builder.RegisterService(&service);
   auto cq = builder.AddCompletionQueue();

   std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
   spdlog::info("starting grpc server on address {}", listen);

   std::thread write_thread([&service, &cq]() {
      service.write_routine(*cq);
   });

   server->Wait();
}