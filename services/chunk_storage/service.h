#pragma once
#include <minepb/chunk_storage.grpc.pb.h>
#include <string_view>

class Service final : public minecpp::chunk_storage::ChunkStorage::Service {
 public:
   explicit Service(std::string_view region_path);
   ~Service() override;
   grpc::Status LoadChunk(grpc::ServerContext *context,
                          const minecpp::chunk_storage::LoadChunkRequest *request,
                          minecpp::chunk::NetChunk *response) override;
 private:
   std::ifstream load_region_file(int x, int z);

   std::string_view region_path;
};
