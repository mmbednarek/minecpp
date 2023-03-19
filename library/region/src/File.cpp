#include <boost/endian/conversion.hpp>
#include <fmt/core.h>
#include <minecpp/region/File.h>

namespace minecpp::region {

RegionFile::RegionFile(std::fstream &s) :
    m_stream(s)
{
}

mb::result<std::vector<uint8_t>, LoadError> RegionFile::load_chunk(int x, int z) noexcept
{
   int off_x = x & 31;
   int off_z = z & 31;

   m_stream.seekg((off_x + off_z * 32) * 4, std::ios::beg);

   uint32_t location;
   m_stream.read((char *) &location, sizeof(uint32_t));
   if (location == 0) {
      return LoadError::RegionNotFound;
   }

   uint32_t offset = location << 8u;
   offset          = boost::endian::big_to_native(offset);
   if (!offset)
      return std::vector<uint8_t>{};
   m_stream.seekg(offset << 12u, std::ios::beg);

   uint32_t data_size;
   m_stream.read((char *) &data_size, sizeof(uint32_t));
   data_size = boost::endian::big_to_native(data_size);

   uint8_t compression;
   m_stream.read((char *) &compression, sizeof(uint8_t));

   std::vector<uint8_t> data(data_size);
   m_stream.read((char *) data.data(), data_size);

   if (m_stream.gcount() != data_size) {
      return LoadError::CorruptedData;
   }

   return data;
}

WriteError RegionFile::write_data(mb::i32 x, mb::i32 z, const mb::view<char> data) noexcept
{
   int off_x = x & 31;
   int off_z = z & 31;

   m_stream.seekg((off_x + off_z * 32) * 4, std::ios::beg);

   mb::u32 location;
   m_stream.read((char *) &location, sizeof(mb::u32));
   if (location == 0) {
      return WriteError::NoChunkAtLocation;
   }

   uint32_t offset = location << 8u;
   offset          = boost::endian::big_to_native(offset);
   if (offset == 0) {
      return WriteError::EmptyOffset;
   }
   mb::u32 block_count = (location >> 24u) & 0xff;

   mb::u32 max_size = (block_count << 12u) - 5;
   if (max_size <= data.size()) {
      // FIXME: add block allocation
      return WriteError::NotEnoughBlocksAllocated;
   }

   m_stream.seekg(offset << 12u, std::ios::beg);

   auto size = static_cast<mb::u32>(data.size());
   size      = boost::endian::native_to_big(size);
   m_stream.write((char *) &size, sizeof(mb::u32));

   mb::u8 compression = 2;
   m_stream.write((char *) &compression, sizeof(mb::u8));
   m_stream.write(data.data(), static_cast<int>(data.size()));

   return WriteError::Ok;
}

}// namespace minecpp::region
