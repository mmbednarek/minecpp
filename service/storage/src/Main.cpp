#include "fdb/Storage.h"
#include "Server.h"
#include "Service.h"
#include <minecpp/proto/service/storage/v1/Storage.pb.h>
#include <spdlog/spdlog.h>

namespace fdb = minecpp::service::storage::fdb;

using minecpp::service::storage::Server;
using minecpp::service::storage::Service;

int main()
{
   auto storage = fdb::Storage::create("clusterfile");
   if (storage == nullptr) {
      return EXIT_FAILURE;
   }

   Server server("127.0.0.1:8080");
   Service service(server, *storage);
   server.set_handler(&service);

   spdlog::info("starting gRPC server on port 8080");
   server.wait();

   //   minecpp::service::storage::proto_chunk::Chunk chunk;
   //   chunk.set_pos_x(1);
   //   chunk.set_pos_z(2);
   //   chunk.mutable_biomes()->Add(3);
   //   if (storage->write_chunk(chunk)) {
   //      spdlog::info("successfully saved chunk");
   //   } else {
   //      spdlog::info("failed to save chunk");
   //   }

   return EXIT_SUCCESS;
}