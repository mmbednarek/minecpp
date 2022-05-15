#include <boost/endian/conversion.hpp>
#include <fmt/core.h>
#include <minecpp/region/file.h>
#include <minecpp/util/format.h>

namespace minecpp::region {

RegionFile::RegionFile(std::fstream &s) : m_stream(s) {}

mb::result<std::vector<uint8_t>> RegionFile::load_chunk(int x, int z) noexcept
{
   //   int off_x = x >= 0 ? x % 32 : -(x % 32);
   //   int off_z = z >= 0 ? z % 32 : -(z % 32);
   int off_x = x & 31;
   int off_z = z & 31;

   m_stream.seekg((off_x + off_z * 32) * 4, std::ios::beg);

   uint32_t location;
   m_stream.read((char *) &location, sizeof(uint32_t));
   if (location == 0) {
      return mb::error(mb::error::status::NotFound, "no chunk at given location");
   }

   uint32_t offset = location << 8u;
   offset          = boost::endian::big_to_native(offset);
   if (!offset)
      return std::vector<uint8_t>();
   m_stream.seekg(offset << 12u, std::ios::beg);

   uint32_t data_size;
   m_stream.read((char *) &data_size, sizeof(uint32_t));
   data_size = boost::endian::big_to_native(data_size);

   uint8_t compression;
   m_stream.read((char *) &compression, sizeof(uint8_t));

   std::vector<uint8_t> data(data_size);
   m_stream.read((char *) data.data(), data_size);

   if (m_stream.gcount() != data_size) {
      return mb::error(fmt::format("(x = {}, z = {}) invalid data count {} != {}", x, z, m_stream.gcount(), data_size));
   }
   return data;
}

mb::result<mb::empty> RegionFile::write_data(mb::i32 x, mb::i32 z, const mb::view<char> data) noexcept
{
   int off_x = x & 31;
   int off_z = z & 31;

   m_stream.seekg((off_x + off_z * 32) * 4, std::ios::beg);

   mb::u32 location;
   m_stream.read((char *) &location, sizeof(mb::u32));
   if (location == 0) {
      return mb::error(mb::error::status::NotFound, "no chunk at given location");
   }

   uint32_t offset = location << 8u;
   offset          = boost::endian::big_to_native(offset);
   if (offset == 0) {
      return mb::error("empty offset");
   }
   mb::u32 block_count = (location >> 24u) & 0xff;

   mb::u32 max_size = (block_count << 12u) - 5;
   if (max_size <= data.size()) {
      // FIXME: add block allocation
      return mb::error("not enough blocks allocated");
   }

   m_stream.seekg(offset << 12u, std::ios::beg);

   mb::u32 size = data.size();
   size         = boost::endian::native_to_big(size);
   m_stream.write((char *) &size, sizeof(mb::u32));

   mb::u8 compression = 2;
   m_stream.write((char *) &compression, sizeof(mb::u8));

   m_stream.write(data.data(), data.size());
   //   for (std::size_t i = 0; i < max_size - data.size(); ++i) {
   //      m_stream.put(0x00); // fill the rest with zeros
   //   }
   return mb::ok;
}

}// namespace minecpp::region
