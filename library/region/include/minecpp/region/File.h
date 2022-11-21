#pragma once
#include <cstdint>
#include <fstream>
#include <mb/int.h>
#include <mb/result.h>
#include <mb/view.h>
#include <memory>
#include <vector>

namespace minecpp::region {

enum class LoadError
{
   RegionNotFound,
   CorruptedData
};

enum class WriteError
{
   Ok,
   NoChunkAtLocation,
   EmptyOffset,
   NotEnoughBlocksAllocated
};

class RegionFile
{
   std::fstream &m_stream;

 public:
   explicit RegionFile(std::fstream &s);

   [[nodiscard]] mb::result<std::vector<uint8_t>, LoadError> load_chunk(int x, int z) noexcept;
   [[nodiscard]] WriteError write_data(mb::i32 x, mb::i32 z, mb::view<char> data) noexcept;
};

}// namespace minecpp::region
