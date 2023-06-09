#include "fdb/Storage.h"
#include "RequestThreadPool.h"
#include "Server.h"
#include "Service.h"

#include <mb/core.h>
#include <spdlog/spdlog.h>

namespace fdb = minecpp::service::storage::fdb;

using minecpp::service::storage::Server;
using minecpp::service::storage::Service;
using minecpp::service::storage::RequestThreadPool;

int main()
{
   auto port             = mb::getenv("PORT").unwrap("8080");
   auto clusterfile_path = mb::getenv("CLUSTERFILE_PATH").unwrap("clusterfile");

   auto storage = fdb::Storage::create(clusterfile_path);
   if (storage == nullptr) {
      return EXIT_FAILURE;
   }

   Server server(static_cast<minecpp::network::Port>(std::stoi(port)));
   Service service(server, *storage);
   RequestThreadPool request_pool{service, 8};

   server.set_handler(&request_pool);

   spdlog::info("starting server on port {}", port);

   for (;;) {
      using namespace std::chrono_literals;
      server.tick();
   }

   return EXIT_SUCCESS;
}