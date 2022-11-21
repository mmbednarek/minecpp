#include "ApiHandler.h"
#include "ChunkSystem.h"
#include "Dispatcher.h"
#include "Entities.h"
#include "EventHandler.h"
#include "EventManager.h"
#include "JobSystem.h"
#include "minecpp/world/population/Object.h"
#include "Players.h"
#include "StorageResponseHandler.h"
#include "World.h"
#include <mb/core.h>
#include <minecpp/repository/Repository.h>
#include <minecpp/service/storage/Storage.h>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

struct Configuration
{
   std::string server_bind_address{};
   std::string server_bind_port{};
   std::vector<std::string> storage_endpoints{};
   std::string resources_data_file{};
   std::uint64_t gameplay_world_seed{};
   int gameplay_max_players{};
   int gameplay_spawn_point_x{};
   int gameplay_spawn_point_y{};
   int gameplay_spawn_point_z{};
   bool debug_logger{};

   void read_from_yaml_file(const std::string &file_name)
   {
      auto yaml_cfg             = YAML::LoadFile(file_name);
      this->server_bind_address = yaml_cfg["server"]["bind_address"].as<std::string>("0.0.0.0");
      this->server_bind_port    = yaml_cfg["server"]["bind_port"].as<std::string>("8000");
      this->storage_endpoints   = yaml_cfg["storage"]["endpoints"].as<std::vector<std::string>>(
              std::vector<std::string>{"127.0.0.1:8080"});
      this->resources_data_file    = yaml_cfg["resources"]["data_file"].as<std::string>("repository.bin");
      this->gameplay_world_seed    = yaml_cfg["gameplay"]["world_seed"].as<unsigned long long>(0ULL);
      this->gameplay_max_players   = yaml_cfg["gameplay"]["max_players"].as<int>(10);
      this->gameplay_spawn_point_x = yaml_cfg["gameplay"]["spawn_point"]["x"].as<int>(0);
      this->gameplay_spawn_point_y = yaml_cfg["gameplay"]["spawn_point"]["y"].as<int>(80);
      this->gameplay_spawn_point_z = yaml_cfg["gameplay"]["spawn_point"]["z"].as<int>(0);
      this->debug_logger           = yaml_cfg["debug_logger"].as<bool>(false);
   }
};

auto main() -> int
{
   using namespace minecpp::service::engine;

   Configuration config;

   auto config_path = mb::getenv("CONFIG_FILE").unwrap("minecpp.yaml");
   config.read_from_yaml_file(config_path);

   if (config.debug_logger) {
      spdlog::set_level(spdlog::level::debug);
   }

   auto load_repo_res = minecpp::repository::load_repository_from_file(config.resources_data_file);
   if (!load_repo_res.ok()) {
      spdlog::error("could not init repository: {}", load_repo_res.err()->msg());
      return 1;
   }

   minecpp::world::population::ObjectRepository::the().register_objects();

   JobSystem job_system{8};

   StorageResponseHandler storage_handler{};
   minecpp::service::storage::StorageClient storage_client(0, &storage_handler, config.storage_endpoints);

   ChunkSystem chunk_system(job_system, storage_client);
   storage_handler.add_handler(&chunk_system);

   EntityManager entities;
   PlayerManager players(entities, {config.gameplay_spawn_point_x, config.gameplay_spawn_point_y,
                                    config.gameplay_spawn_point_z});

   EventManager manager;
   Dispatcher dispatcher(manager);
   minecpp::controller::BlockManager block_manager;

   World world(boost::uuids::uuid(), chunk_system, job_system, dispatcher, players, entities, block_manager);
   EventHandler handler(dispatcher, players, entities, world, block_manager);

   ApiHandler api_handler(handler, manager,
                          fmt::format("{}:{}", config.server_bind_address, config.server_bind_port));

   spdlog::info("starting gRPC server on address {}:{}", config.server_bind_address, config.server_bind_port);
   if (auto res = api_handler.wait(); not res.ok()) {
      spdlog::error("server error: {}", res.err()->msg());
   }
}