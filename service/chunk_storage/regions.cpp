#include "regions.h"
#include <fmt/core.h>
#include <minecpp/error/result.h>
#include <minecpp/region/file.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <utility>

namespace ChunkStorage {

RegionFile::RegionFile(std::fstream stream, std::string path) : m_file(std::move(stream)), m_path(std::move(path)) {}

mb::result<std::unique_ptr<RegionFile>> RegionFile::load(const std::string &path) {
   std::fstream file(path, std::ios_base::binary | std::ios_base::out | std::ios_base::in);
   if (!file.is_open()) {
      return mb::error(mb::error::status::NotFound, "file not found");
   }
   return std::make_unique<RegionFile>(std::move(file), path);
}

mb::result<mb::empty> RegionFile::reload() {
   m_file.close();
   m_file.open(m_path, std::ios_base::binary | std::ios_base::out | std::ios_base::in);
   if (!m_file.is_open()) {
      return mb::error("could not reopen file");
   }
   return mb::ok;
}

Regions::Regions(std::string_view path) : m_path(path) {}

constexpr int max_z = 62502;// two regions over world border
static constexpr int64_t hash_chunk_pos(int x, int z) {
   return static_cast<int64_t>(z) + max_z * static_cast<int64_t>(x);
}

mb::result<RegionFile &> Regions::get_region(int x, int z) {
   auto iter = m_files.find(hash_chunk_pos(x, z));
   if (iter != m_files.end()) {
      return *iter->second;
   }
   return load_region(x, z);
}

mb::result<RegionFile &> Regions::load_region(int x, int z) {
   auto region_path = fmt::format("{}/r.{}.{}.mca", m_path, x, z);
   spdlog::info("loading region file {}", region_path);
   auto region = MB_TRY(RegionFile::load(region_path));
   auto hash = hash_chunk_pos(x, z);
   auto &region_ref = *region;
   m_files[hash] = std::move(region);
   return region_ref;
}

static constexpr int chunk_to_region(int cord) { return cord < 0 ? (cord / 32 - 1) : cord / 32; }

mb::result<std::vector<uint8_t>> Regions::read_chunk(int x, int z) {
   auto &region = MB_TRY(get_region(chunk_to_region(x), chunk_to_region(z)));
   std::lock_guard<std::mutex> lock(region.m_mutex);

   minecpp::region::RegionFile r(region.m_file);
   return r.load_chunk(x, z);
}

mb::result<mb::empty> Regions::write_chunk(mb::i32 x, mb::i32 z, const mb::view<char> chunk_data) noexcept {
   auto &region = MB_TRY(get_region(chunk_to_region(x), chunk_to_region(z)));
   std::lock_guard<std::mutex> lock(region.m_mutex);

   minecpp::region::RegionFile r(region.m_file);
   MB_TRY(r.write_data(x, z, chunk_data));
   return mb::ok;
}

}// namespace ChunkStorage
