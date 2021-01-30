#pragma once
#include <any>
#include <cstdint>
#include <minecpp/error/result.h>
#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string_view>

namespace ChunkStorage {

struct RegionFile {
   std::fstream file;
   std::string path;
   std::mutex m;

   explicit RegionFile(std::fstream stream, const std::string &path);
   ~RegionFile();
   static result<std::unique_ptr<RegionFile>> load(const std::string &path);
};

class Regions {
   std::string_view path;

   std::map<int64_t, std::unique_ptr<RegionFile>> files;

 public:
   explicit Regions(std::string_view path);

   result<std::vector<uint8_t>> read_chunk(int x, int z);

 private:
   result<RegionFile &> get_region(int x, int z);
   result<RegionFile &> load_region(int x, int z);
};

}// namespace ChunkStorage
