#include "service.h"
#include <minecpp/game/chunk/chunk.h>
#include <minecpp/region/file.h>
#include <minecpp/util/compression.h>
#include <minecpp/util/format.h>
#include <minecpp/util/grpc.h>
#include <minecpp/util/uuid.h>
#include <spdlog/spdlog.h>

namespace ChunkStorage {

Service::Service(std::string_view region_path) : chunks(Regions(region_path)) {}

grpc::Status Service::LoadChunk(grpc::ServerContext *context, const minecpp::chunk_storage::LoadChunkRequest *request,
                                minecpp::chunk::NetChunk *response) {
   auto &chunk = MCPP_GRPC_TRY(chunks.get_chunk(request->x(), request->z()));
   for (const auto &sec : chunk.m_sections) {
      if (!sec.second.sky_light.empty() && sec.second.sky_light.size() != 4096) {
         spdlog::info("invalid sky light size: {}", sec.second.sky_light.size());
      }
   }

   chunk.as_proto(response);
   return grpc::Status();
}

grpc::Status Service::SetBlock(grpc::ServerContext *context, const minecpp::chunk_storage::SetBlockRequest *request,
                               minecpp::chunk_storage::EmptyResponse *response) {
   MCPP_GRPC_TRY(chunks.set_block(request->x(), request->y(), request->z(), request->state()));
   return grpc::Status();
}

Service::~Service() {}

grpc::Status Service::AddReferences(grpc::ServerContext *context,
                                    const minecpp::chunk_storage::AddReferencesRequest *request,
                                    minecpp::chunk_storage::AddReferencesResponse *response) {
   std::vector<minecpp::game::block::ChunkPos> coords(request->coords_size());
   std::transform(request->coords().begin(), request->coords().begin(), coords.begin(), [](auto &in_coord) -> minecpp::game::block::ChunkPos {
      return minecpp::game::block::ChunkPos(in_coord.x(), in_coord.z());
   });

   auto engine_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->engine_id()));
   auto player_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->player_id()));

   auto target = MCPP_GRPC_TRY(chunks.add_refs(engine_id, player_id, coords));
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
   std::vector<minecpp::game::block::ChunkPos> coords(request->coords_size());
   std::transform(request->coords().begin(), request->coords().begin(), coords.begin(), [](auto &in_coord) -> minecpp::game::block::ChunkPos {
      return minecpp::game::block::ChunkPos(in_coord.x(), in_coord.z());
   });
   auto player_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->player_id()));

   MCPP_GRPC_TRY(chunks.free_refs(player_id, coords));
   return grpc::Status();
}
grpc::Status Service::HeightAt(grpc::ServerContext *context, const minecpp::chunk_storage::HeightAtRequest *request,
                               minecpp::chunk_storage::HeightAtResponse *response) {
   response->set_height(MCPP_GRPC_TRY(chunks.height_at(request->x(), request->z())));
   return grpc::Status();
}

}// namespace ChunkStorage
