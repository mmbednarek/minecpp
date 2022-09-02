#include "Service.h"
#include <minecpp/region/File.h>
#include <minecpp/util/Compression.h>
#include <minecpp/util/Format.h>
#include <minecpp/util/Grpc.h>
#include <minecpp/util/Uuid.h>
#include <minecpp/world/Chunk.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::chunk_storage {

Service::Service(std::string_view region_path) :
    chunks(Regions(region_path))
{
}

grpc::Status Service::LoadChunk(grpc::ServerContext *context,
                                const chunk_storage_v1::LoadChunkRequest *request, chunk_v1::Chunk *response)
{
   auto &chunk = MCPP_GRPC_TRY(chunks.get_chunk(request->x(), request->z()));
   chunk.as_proto(response);
   return grpc::Status();
}

grpc::Status Service::SetBlock(grpc::ServerContext *context, const chunk_storage_v1::SetBlockRequest *request,
                               chunk_storage_v1::EmptyResponse *response)
{
   MCPP_GRPC_TRY(chunks.set_block(request->x(), request->y(), request->z(), request->state()));
   return grpc::Status();
}

Service::~Service() = default;

grpc::Status Service::AddReferences(grpc::ServerContext *context,
                                    const chunk_storage_v1::AddReferencesRequest *request,
                                    chunk_storage_v1::AddReferencesResponse *response)
{
   std::vector<minecpp::game::ChunkPosition> coords(static_cast<std::size_t>(request->coords_size()));
   std::transform(request->coords().begin(), request->coords().end(), coords.begin(),
                  [](auto &in_coord) -> minecpp::game::ChunkPosition {
                     return {in_coord.x(), in_coord.z()};
                  });

   auto engine_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->engine_id()));
   auto player_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->player_id()));

   auto target = MCPP_GRPC_TRY(chunks.add_refs(engine_id, player_id, coords));
   if (target.is_nil()) {
      response->set_status(chunk_storage_v1::ReferenceStatus::OK);
      return grpc::Status();
   }

   response->set_status(chunk_storage_v1::ReferenceStatus::MUST_MOVE);
   response->set_target_engine_id(target.data, target.size());
   return grpc::Status();
}

grpc::Status Service::RemoveReference(grpc::ServerContext *context,
                                      const chunk_storage_v1::RemoveReferencesRequest *request,
                                      chunk_storage_v1::EmptyResponse *response)
{
   std::vector<minecpp::game::ChunkPosition> coords(static_cast<std::size_t>(request->coords_size()));
   std::transform(request->coords().begin(), request->coords().end(), coords.begin(),
                  [](auto &in_coord) -> minecpp::game::ChunkPosition {
                     return {in_coord.x(), in_coord.z()};
                  });
   auto player_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->player_id()));

   MCPP_GRPC_TRY(chunks.free_refs(player_id, coords));
   return {};
}

grpc::Status Service::HeightAt(grpc::ServerContext *context, const chunk_storage_v1::HeightAtRequest *request,
                               chunk_storage_v1::HeightAtResponse *response)
{
   response->set_height(MCPP_GRPC_TRY(chunks.height_at(request->x(), request->z())));
   return {};
}

grpc::Status Service::GetBlock(::grpc::ServerContext *context,
                               const ::minecpp::proto::common::v1::BlockPosition *request,
                               ::minecpp::proto::common::v1::BlockState *response)
{
   auto block_pos = game::BlockPosition::from_proto(*request);
   auto chunk_pos = block_pos.chunk_position();
   auto chunk     = MCPP_GRPC_TRY(chunks.get_chunk(chunk_pos));
   auto block_state = chunk.get_block(block_pos);
   if (block_state.has_failed())
      return {grpc::StatusCode::INTERNAL, "could not obtain block"};

   response->set_block_state(*block_state);
   return {};
}

grpc::Status
Service::GetLightLevel(::grpc::ServerContext * /*context*/,
                       const ::minecpp::proto::service::chunk_storage::v1::GetLightLevelRequest *request,
                       ::minecpp::proto::common::v1::LightLevel *response)
{
   auto block_pos = game::BlockPosition::from_proto(request->position());
   auto chunk_pos = block_pos.chunk_position();

   auto chunk = chunks.get_chunk(chunk_pos);
   if (chunk.has_failed()) {
      return {grpc::StatusCode::INVALID_ARGUMENT, chunk.err()->msg()};
   }

   mb::result<game::LightValue> lightLevel =
           chunk->get_light(game::LightType::from_proto(request->light_type()), block_pos);
   if (lightLevel.has_failed()) {
      return {grpc::StatusCode::INVALID_ARGUMENT, lightLevel.err()->msg()};
   }

   response->set_level(*lightLevel);
   return {};
}

grpc::Status
Service::SetLightLevel(::grpc::ServerContext * /*context*/,
                       const ::minecpp::proto::service::chunk_storage::v1::SetLightLevelRequest *request,
                       ::minecpp::proto::service::chunk_storage::v1::EmptyResponse * /*response*/)
{
   auto block_pos = game::BlockPosition::from_proto(request->position());
   auto chunk_pos = block_pos.chunk_position();

   auto chunk = chunks.get_chunk(chunk_pos);
   if (chunk.has_failed()) {
      return {grpc::StatusCode::INVALID_ARGUMENT, chunk.err()->msg()};
   }

   auto result = chunk->set_light(game::LightType::from_proto(request->light_type()), block_pos,
                                  static_cast<game::LightValue>(request->level().level()));
   if (result.has_failed()) {
      return {grpc::StatusCode::INVALID_ARGUMENT, result.err()->msg()};
   }

   return {};
}

grpc::Status Service::GetSlice(::grpc::ServerContext *context,
                               const ::minecpp::proto::common::v1::SectionRange *request,
                               ::minecpp::proto::chunk::v1::SectionSlice *response)
{
   auto slice = chunks.get_slice(game::SectionRange::from_proto(*request));
   if (slice.has_failed()) {
      return {grpc::StatusCode::INVALID_ARGUMENT, slice.err()->msg()};
   }
   *response = slice->to_proto();
   return {};
}

grpc::Status Service::ApplySlice(::grpc::ServerContext *context,
                                 const ::minecpp::proto::chunk::v1::SectionSlice *request,
                                 ::minecpp::proto::service::chunk_storage::v1::EmptyResponse *response)
{
   auto section_slice = world::SectionSlice::from_proto(*request);
   auto res           = chunks.apply_slice(section_slice);
   if (res.has_failed()) {
      return {grpc::StatusCode::INVALID_ARGUMENT, res.err()->msg()};
   }
   return {};
}

}// namespace minecpp::service::chunk_storage
