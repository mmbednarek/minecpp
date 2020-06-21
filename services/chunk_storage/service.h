#pragma once
#include "chunks.h"
#include <minepb/chunk_storage.grpc.pb.h>
#include <string_view>

namespace ChunkStorage {

class Service final : public minecpp::chunk_storage::ChunkStorage::Service {
   ChunkManager chunks;
 public:
   explicit Service(std::string_view region_path);
   ~Service() override;
   grpc::Status LoadChunk(grpc::ServerContext *context,
                          const minecpp::chunk_storage::LoadChunkRequest *request,
                          minecpp::chunk::NetChunk *response) override;

   grpc::Status
   SetBlock(grpc::ServerContext *context,
            const minecpp::chunk_storage::SetBlockRequest *request,
            minecpp::chunk_storage::EmptyResponse *response) override;
};

}
