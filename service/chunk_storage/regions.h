#pragma once
#include <any>
#include <cstdint>
#include <fstream>
#include <functional>
#include <map>
#include <mb/result.h>
#include <mb/view.h>
#include <memory>
#include <mutex>
#include <string_view>

namespace minecpp::service::chunk_storage {

struct RegionFile {
   std::fstream m_file;
   std::string m_path;
   std::mutex m_mutex;

   explicit RegionFile(std::fstream stream, std::string path);
   static mb::result<std::unique_ptr<RegionFile>> load(const std::string &path);
   [[nodiscard]] mb::result<mb::empty> reload();
};

class Regions {
   std::string_view m_path;
   std::map<int64_t, std::unique_ptr<RegionFile>> m_files;

 public:
   explicit Regions(std::string_view path);

   [[nodiscard]] mb::result<std::vector<uint8_t>> read_chunk(int x, int z);
   [[nodiscard]] mb::result<mb::empty> write_chunk(mb::i32 x, mb::i32 z, mb::view<char> chunk_data) noexcept;

 private:
   mb::result<RegionFile &> get_region(int x, int z);
   mb::result<RegionFile &> load_region(int x, int z);
};

}// namespace minecpp::service::chunk_storage
