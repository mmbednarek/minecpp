#include <boost/endian/conversion.hpp>
#include <minecpp/util/format.h>
#include <minecpp/region/reader.h>

namespace Region {

Reader::Reader(std::istream &s) : stream(s) {}

result<std::vector<uint8_t>> Reader::load_chunk(int x, int z) {
   //   int off_x = x >= 0 ? x % 32 : -(x % 32);
   //   int off_z = z >= 0 ? z % 32 : -(z % 32);
   int off_x = x & 31;
   int off_z = z & 31;

   stream.seekg((off_x + off_z * 32) * 4);

   uint32_t location;
   stream.read((char *) &location, sizeof(uint32_t));
   if (location == 0) {
      return error(errclass::NotFound, "no chunk at given location");
   }

   uint32_t offset = location << 8u;
   offset = boost::endian::big_to_native(offset);
   if (!offset)
      return std::vector<uint8_t>();
   stream.seekg(offset << 12u);

   uint32_t data_size;
   stream.read((char *) &data_size, sizeof(uint32_t));
   data_size = boost::endian::big_to_native(data_size);

   uint8_t compression;
   stream.read((char *) &compression, sizeof(uint8_t));

   std::vector<uint8_t> data(data_size);
   stream.read((char *) data.data(), data_size);

   if (stream.gcount() != data_size) {
      return errorf("(x = {}, z = {}) invalid data count {} != {}", x, z,
                    stream.gcount(), data_size);
   }

   return data;
}

}// namespace Region
