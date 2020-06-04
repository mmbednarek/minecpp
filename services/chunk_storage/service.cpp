#include "service.h"
#include <fstream>
#include <game/chunk/netchunk.h>
#include <mineutils/compression.h>
#include <mineutils/format.h>
#include <nbt/reader.h>
#include <region/reader.h>

Service::Service(std::string_view region_path) : region_path(region_path) {}

grpc::Status
Service::LoadChunk(grpc::ServerContext *context,
                   const minecpp::chunk_storage::LoadChunkRequest *request,
                   minecpp::chunk::NetChunk *response) {
   std::stringstream path;
   path << region_path << "/r." << (request->x() / 32) << "."
        << (request->z() / 32) << ".mca";

   auto region_file = load_region_file(request->x() / 32, request->z() / 32);
   if (!region_file.is_open()) {
      return grpc::Status(grpc::StatusCode::NOT_FOUND,
                          Utils::format("could not find file {}", path.str()));
   }

   try {
      Region::Reader r(region_file);
      auto compressed_chunk = r.load_chunk(request->x(), request->z());
      std::istringstream compressed_stream(std::string(
          (char *)compressed_chunk.data(), compressed_chunk.size()));

      Utils::ZlibInputStream chunk_stream(compressed_stream);
      NBT::Reader cr(chunk_stream);
      cr.check_signature();
      cr.find_compound("Level");
      Game::NetChunk(cr).as_proto(response);
      return grpc::Status();
   } catch (std::runtime_error &e) {
      return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
   }
}

std::ifstream Service::load_region_file(int x, int z) {
   std::stringstream path;
   path << region_path << "/r." << x << "." << z << ".mca";
   return std::ifstream(path.str());
}

Service::~Service() {}
