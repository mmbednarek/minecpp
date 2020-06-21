#include "service.h"
#include <fstream>
#include <game/chunk/netchunk.h>
#include <mineutils/compression.h>
#include <mineutils/format.h>
#include <nbt/reader.h>
#include <region/reader.h>
#include <spdlog/spdlog.h>

namespace ChunkStorage {

Service::Service(std::string_view region_path) : chunks(Regions(region_path)) {}

grpc::Status
Service::LoadChunk(grpc::ServerContext *context,
                   const minecpp::chunk_storage::LoadChunkRequest *request,
                   minecpp::chunk::NetChunk *response) {
   try {
      chunks.get_chunk(request->x(), request->z()).as_proto(response);
      return grpc::Status();
   } catch (std::runtime_error &e) {
      spdlog::error("internal error: {}", e.what());
      return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
   }
}

grpc::Status
Service::SetBlock(grpc::ServerContext *context,
                  const minecpp::chunk_storage::SetBlockRequest *request,
                  minecpp::chunk_storage::EmptyResponse *response) {
   chunks.set_block(request->x(), request->y(), request->z(), request->state());
   return grpc::Status();
}

Service::~Service() {}

} // namespace ChunkStorage
