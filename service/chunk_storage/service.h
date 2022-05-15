#pragma once
#include "chunks.h"
#include <minecpp/proto/service/chunk_storage/v1/chunk_storage.grpc.pb.h>
#include <string_view>

namespace minecpp::service::chunk_storage {

namespace chunk_storage_v1 = minecpp::proto::service::chunk_storage::v1;
namespace chunk_v1         = minecpp::proto::chunk::v1;

class Service final : public chunk_storage_v1::ChunkStorage::Service
{
   ChunkManager chunks;

 public:
   explicit Service(std::string_view region_path);
   ~Service() override;
   grpc::Status LoadChunk(grpc::ServerContext *context, const chunk_storage_v1::LoadChunkRequest *request,
                          chunk_v1::Chunk *response) override;

   grpc::Status SetBlock(grpc::ServerContext *context, const chunk_storage_v1::SetBlockRequest *request,
                         chunk_storage_v1::EmptyResponse *response) override;

   grpc::Status AddReferences(grpc::ServerContext *context, const chunk_storage_v1::AddReferencesRequest *request,
                              chunk_storage_v1::AddReferencesResponse *response) override;

   grpc::Status RemoveReference(grpc::ServerContext *context, const chunk_storage_v1::RemoveReferencesRequest *request,
                                chunk_storage_v1::EmptyResponse *response) override;

   grpc::Status HeightAt(grpc::ServerContext *context, const chunk_storage_v1::HeightAtRequest *request,
                         chunk_storage_v1::HeightAtResponse *response) override;
   grpc::Status GetBlock(::grpc::ServerContext *context, const ::minecpp::proto::common::v1::BlockPosition *request,
                         ::minecpp::proto::common::v1::BlockState *response) override;
};

}// namespace minecpp::service::chunk_storage
