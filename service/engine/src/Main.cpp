#include "ApiHandler.h"
#include "ChunkSystem.h"
#include "Dispatcher.h"
#include "Entities.h"
#include "EventHandler.h"
#include "EventManager.h"
#include "job/ChunkIsPresent.h"
#include "JobSystem.h"
#include "Players.h"
#include "StorageResponseHandler.h"
#include "World.h"
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <mb/core.h>
#include <minecpp/proto/service/chunk_storage/v1/ChunkStorage.grpc.pb.h>
#include <minecpp/repository/Repository.h>
#include <minecpp/service/storage/Storage.h>
#include <spdlog/spdlog.h>

auto main() -> int
{
   using namespace minecpp::service::engine;

   auto player_path           = mb::getenv("PLAYERS_PATH").unwrap("world/playerdata");
   auto chunk_storage_address = mb::getenv("CHUNK_STORAGE_ADDRESS").unwrap("127.0.0.1:7000");
   auto listen                = mb::getenv("LISTEN").unwrap("0.0.0.0:7800");
   auto repo_file             = mb::getenv("REPOSITORY_FILENAME").unwrap("repository.bin");

   auto load_repo_res = minecpp::repository::load_repository_from_file(repo_file);
   if (!load_repo_res.ok()) {
      spdlog::error("could not init repository: {}", load_repo_res.err()->msg());
      return 1;
   }

   StorageResponseHandler storage_handler{};

   JobSystem job_system{1};

   minecpp::service::storage::StorageClient storage_client(0, &storage_handler, {"127.0.0.1:8080"});

   ChunkSystem chunk_system(job_system, storage_client);
   storage_handler.add_handler(&chunk_system);

   EntityManager entities;
   PlayerManager players(player_path, entities);

   auto channel       = grpc::CreateChannel(chunk_storage_address, grpc::InsecureChannelCredentials());
   auto chunk_storage = minecpp::proto::service::chunk_storage::v1::ChunkStorage::NewStub(channel);

   EventManager manager;
   Dispatcher dispatcher(manager);
   minecpp::controller::BlockManager block_manager;
   World world(boost::uuids::uuid(), *chunk_storage, dispatcher, players, entities, block_manager);
   EventHandler handler(dispatcher, players, entities, world, block_manager);

   job_system.when<job::ChunkIsPresent>(chunk_system, minecpp::game::ChunkPosition(0, 0)).run([&] {
      auto *chunk = chunk_system.chunk_at({0, 0});
      if (chunk == nullptr) {
         spdlog::info("failed to obtain chunk");
         return;
      }
      chunk->set_block({3, 4, 5}, 2);

      spdlog::info("successfully applied block");
   });

   ApiHandler api_handler(handler, manager, listen);

   spdlog::info("starting grpc server on address {}", listen);
   if (auto res = api_handler.wait(); not res.ok()) {
      spdlog::error("server error: {}", res.err()->msg());
   }
}