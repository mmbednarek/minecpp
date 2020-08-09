#include "service.h"
#include <fstream>
#include <game/chunk/chunk.h>
#include <mineutils/compression.h>
#include <mineutils/format.h>
#include <mineutils/uuid.h>
#include <nbt/reader.h>
#include <region/reader.h>
#include <spdlog/spdlog.h>

namespace ChunkStorage {

Service::Service(std::string_view region_path) : chunks(Regions(region_path)) {}

grpc::Status Service::LoadChunk(grpc::ServerContext *context, const minecpp::chunk_storage::LoadChunkRequest *request,
                                minecpp::chunk::NetChunk *response) {
   try {
      auto res = chunks.get_chunk(request->x(), request->z());
      if (!res.ok()) {
         return res.err()->grpc_status();
      }
      res.unwrap().as_proto(response);
      return grpc::Status();
   } catch (std::runtime_error &e) {
      spdlog::error("internal error: {}", e.what());
      return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
   }
}

grpc::Status Service::SetBlock(grpc::ServerContext *context, const minecpp::chunk_storage::SetBlockRequest *request,
                               minecpp::chunk_storage::EmptyResponse *response) {
   auto res = chunks.set_block(request->x(), request->y(), request->z(), request->state());
   if (!res.ok()) {
      return res.err()->grpc_status();
   }
   return grpc::Status();
}

Service::~Service() {}

grpc::Status Service::AddReferences(grpc::ServerContext *context,
                                    const minecpp::chunk_storage::AddReferencesRequest *request,
                                    minecpp::chunk_storage::AddReferencesResponse *response) {
   std::vector<Game::Block::ChunkPos> coords(request->coords_size());
   std::size_t i = 0;
   for (const auto &coord : request->coords()) {
      coords[i] = Game::Block::ChunkPos(coord.x(), coord.z());
      ++i;
   }

   uuid engine_id;
   Utils::decode_uuid(engine_id, request->engine_id().data());
   uuid player_id;
   Utils::decode_uuid(player_id, request->player_id().data());

   auto res = chunks.add_refs(engine_id, player_id, coords);
   if (!res.ok()) {
      return res.err()->grpc_status();
   }
   auto target = res.unwrap();
   if (target.is_nil()) {
      response->set_status(minecpp::chunk_storage::ReferenceStatus::OK);
      return grpc::Status();
   }

   response->set_status(minecpp::chunk_storage::ReferenceStatus::MUST_MOVE);
   response->set_target_engine_id(target.data, target.size());
   return grpc::Status();
}
grpc::Status Service::RemoveReference(grpc::ServerContext *context,
                                      const minecpp::chunk_storage::RemoveReferencesRequest *request,
                                      minecpp::chunk_storage::EmptyResponse *response) {
   return grpc::Status();
}
grpc::Status Service::HeightAt(grpc::ServerContext *context, const minecpp::chunk_storage::HeightAtRequest *request,
                               minecpp::chunk_storage::HeightAtResponse *response) {
   auto height_res = chunks.height_at(request->x(), request->z());
   if (!height_res.ok()) {
      return height_res.err()->grpc_status();
   }
   response->set_height(height_res.unwrap(0));
   return grpc::Status();
}

}// namespace ChunkStorage
