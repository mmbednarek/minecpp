#include "fdb/Storage.h"
#include "Server.h"
#include "Service.h"
#include <mb/core.h>
#include <spdlog/spdlog.h>

namespace fdb = minecpp::service::storage::fdb;

using minecpp::service::storage::Server;
using minecpp::service::storage::Service;

int main()
{
   auto listen = mb::getenv("LISTEN").unwrap("0.0.0.0:8080");
   auto clusterfile_path = mb::getenv("CLUSTERFILE_PATH").unwrap("clusterfile");

   auto storage = fdb::Storage::create(clusterfile_path);
   if (storage == nullptr) {
      return EXIT_FAILURE;
   }

   Server server(listen);
   Service service(server, *storage);
   server.set_handler(&service);

   spdlog::info("starting gRPC server on address {}", listen);
   server.wait();

   return EXIT_SUCCESS;
}