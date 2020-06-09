#include "service.h"
#include <boost/log/trivial.hpp>
#include <fstream>
#include <game/chunk/netchunk.h>
#include <mineutils/compression.h>
#include <mineutils/format.h>
#include <nbt/reader.h>
#include <region/reader.h>

Service::Service(std::string_view region_path) : region_path(region_path) {}

int chunk_to_region(int cord) {
   if (cord < 0) {
      return cord / 32 - 1;
   }
   return cord / 32;
}

grpc::Status
Service::LoadChunk(grpc::ServerContext *context,
                   const minecpp::chunk_storage::LoadChunkRequest *request,
                   minecpp::chunk::NetChunk *response) {
   auto region_file = load_region_file(chunk_to_region(request->x()),
                                       chunk_to_region(request->z()));
   if (!region_file.is_open()) {
      BOOST_LOG_TRIVIAL(info)
          << "no region at: x = " << request->x() << ", z = " << request->z();
      return grpc::Status(grpc::StatusCode::NOT_FOUND, "could not find region file");
   }

   try {
      Region::Reader r(region_file);
      auto compressed_chunk = r.load_chunk(request->x(), request->z());
      std::istringstream compressed_stream(std::string(
          (char *)compressed_chunk.data(), compressed_chunk.size()));

      BOOST_LOG_TRIVIAL(info) << "sending chunk x = " << request->x() << ", z = " << request->z();

      Utils::ZlibInputStream chunk_stream(compressed_stream);
      NBT::Reader cr(chunk_stream);
      cr.check_signature();
      cr.find_compound("Level");
      Game::NetChunk(cr).as_proto(response);
      region_file.close();
      return grpc::Status();
   } catch (std::runtime_error &e) {
      BOOST_LOG_TRIVIAL(info) << "INTERNAL ERROR: " << e.what();
      region_file.close();
      return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
   }
}

std::ifstream Service::load_region_file(int x, int z) {
   std::stringstream path;
   path << region_path << "/r." << x << "." << z << ".mca";
   return std::ifstream(path.str());
}

Service::~Service() {}
