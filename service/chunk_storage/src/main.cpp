#include "service.h"
#include <grpcpp/server_builder.h>
#include <mb/core.h>
#include <minecpp/game/worldgen/population/object.h>
#include <minecpp/repository/repository.h>
#include <spdlog/spdlog.h>

auto main() -> int
{
   auto region_path = mb::getenv("REGION_PATH").unwrap("world/region");
   auto listen      = mb::getenv("LISTEN").unwrap("0.0.0.0:7600");
   auto repo_file   = mb::getenv("REPOSITORY_FILENAME").unwrap("repository.bin");

   auto load_repo_res = minecpp::repository::load_repository_from_file(repo_file);
   if (!load_repo_res.ok()) {
      spdlog::error("could not load repository: {}", load_repo_res.err()->msg());
      return 1;
   }

   minecpp::game::worldgen::population::ObjectRepository::the().register_objects();

   minecpp::service::chunk_storage::Service service(region_path);

   grpc::ServerBuilder builder;
   builder.AddListeningPort(listen, grpc::InsecureServerCredentials());
   builder.RegisterService(&service);

   std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
   spdlog::info("starting grpc server on address {}", listen);
   server->Wait();
}
