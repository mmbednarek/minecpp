#pragma once
#include <any>
#include <cstdint>
#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string_view>

namespace ChunkStorage {

struct RegionFile {
   std::fstream file;
   std::mutex m;

   explicit RegionFile(const std::string &filename);
};

class Regions {
   std::string_view path;

   std::map<int64_t, std::unique_ptr<RegionFile>> files;

 public:
   explicit Regions(std::string_view path);

   std::any read_region(int x, int z,
                        const std::function<std::any(std::fstream &file)> &f);

 private:
   RegionFile &get_region(int x, int z);
   RegionFile &load_region(int x, int z);
};

} // namespace ChunkStorage
