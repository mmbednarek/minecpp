#include "regions.h"
#include <minecpp/error/result.h>
#include <minecpp/region/reader.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <utility>

namespace ChunkStorage {

RegionFile::RegionFile(std::fstream stream, const std::string &path) : file(std::move(stream)), path(std::move(path)) {}

mb::result<std::unique_ptr<RegionFile>> RegionFile::load(const std::string &path) {
   std::fstream file;
   file.open(path);
   if (!file.is_open()) {
      return mb::error(mb::error::status::NotFound, "file not found");
   }
   return std::make_unique<RegionFile>(std::move(file), path);
}

RegionFile::~RegionFile() {
   file.close();
}

Regions::Regions(std::string_view path) : path(path) {}

constexpr int max_z = 62502;// two regions over world border
static constexpr int64_t hash_chunk_pos(int x, int z) {
   return static_cast<int64_t>(z) + max_z * static_cast<int64_t>(x);
}

mb::result<RegionFile &> Regions::get_region(int x, int z) {
   auto iter = files.find(hash_chunk_pos(x, z));
   if (iter != files.end()) {
      return *iter->second;
   }
   return load_region(x, z);
}

mb::result<RegionFile &> Regions::load_region(int x, int z) {
   std::stringstream region_path;
   region_path << path << "/r." << x << "." << z << ".mca";

   spdlog::info("loading region file {}", region_path.str());

   auto region = tryget(RegionFile::load(region_path.str()));
   auto hash = hash_chunk_pos(x, z);
   auto &region_ref = *region;
   files[hash] = std::move(region);
   return region_ref;
}

static constexpr int chunk_to_region(int cord) { return cord < 0 ? (cord / 32 - 1) : cord / 32; }

mb::result<std::vector<uint8_t>> Regions::read_chunk(int x, int z) {
   auto region_res = get_region(chunk_to_region(x), chunk_to_region(z));
   if (!region_res.ok()) {
      return region_res.err();
   }
   auto &region = region_res.unwrap();

   region.m.lock();

   minecpp::region::Reader r(region.file);
   auto data = r.load_chunk(x, z);
   region.m.unlock();
   if (!data.ok()) {
      return data.err();
   }
   return data.unwrap();
}

}// namespace ChunkStorage
