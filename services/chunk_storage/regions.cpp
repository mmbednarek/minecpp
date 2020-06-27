#include "regions.h"
#include <spdlog/spdlog.h>
#include <sstream>

namespace ChunkStorage {

RegionFile::RegionFile(const std::string &filename) {
   file.open(filename);
   if (!file.is_open()) {
      throw std::runtime_error("file not opened");
   }
}

Regions::Regions(std::string_view path) : path(path) {}

std::any
Regions::read_region(int x, int z,
                     const std::function<std::any(std::fstream &)> &f) {
   auto &region = get_region(x, z);
   region.m.lock();
   std::any result;
   try {
      result = f(region.file);
   } catch (std::runtime_error &e) {
      spdlog::info("exception while region transact: {}", e.what());
      region.m.unlock();
      throw e;
   }
   region.m.unlock();

   return result;
}

constexpr int max_z = 62502; // two regions over world border
static constexpr int64_t hash_chunk_pos(int x, int z) {
   return static_cast<int64_t>(z) + max_z * static_cast<int64_t>(x);
}

RegionFile &Regions::get_region(int x, int z) {
   auto iter = files.find(hash_chunk_pos(x, z));
   if (iter != files.end()) {
      return *iter->second;
   }

   return load_region(x, z);
}

RegionFile &Regions::load_region(int x, int z) {
   std::stringstream region_path;
   region_path << path << "/r." << x << "." << z << ".mca";

   spdlog::info("loading region file {}", region_path.str());

   files[hash_chunk_pos(x, z)] = std::make_unique<RegionFile>(region_path.str());

   return *files[hash_chunk_pos(x, z)];
}

} // namespace ChunkStorage
