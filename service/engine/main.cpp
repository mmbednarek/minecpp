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
#include <minecpp/grpc/server/bidi.h>
#include <minecpp/proto/service/chunk_storage/v1/chunk_storage.grpc.pb.h>
#include <spdlog/spdlog.h>

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

   EventManager<BidiStream> manager;
   Dispatcher dispatcher(manager);
   World world(boost::uuids::uuid(), *chunk_storage, dispatcher);
   EventHandler handler(dispatcher, players, entities, world);

   ApiHandler api_handler(handler, manager);
   using BidiServer = minecpp::grpc::server::BidiServer<minecpp::proto::service::engine::v1::EngineService::AsyncService, minecpp::proto::event::clientbound::v1::Event, minecpp::proto::event::serverbound::v1::Event, ApiHandler, std::string, &minecpp::proto::service::engine::v1::EngineService::AsyncService::RequestJoin>;
   BidiServer server(listen, api_handler, 4);
   spdlog::info("starting grpc server on address {}", listen);
   server.accept();
   auto res = server.wait();
   if (!res.ok()) {
      spdlog::error("server error: {}", res.msg());
   }
}