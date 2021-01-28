#include <minecpp/network/msg/writer.h>
#include <boost/uuid/uuid_io.hpp>
#include <cstring>
#include <minecpp/util/compression.h>

namespace MineNet::Message {

Writer::Writer() {}

void Writer::write_byte(uint8_t value) {
   stream.write((char *)&value, sizeof(uint8_t));
}

void Writer::write_varint(uint32_t value) {
   for (;;) {
      if (value & (~0x7Fu)) {
         write_byte((value & 0x7Fu) | 0x80u);
         value >>= 7;
         continue;
      }
      write_byte(value);
      break;
   }
}

void Writer::write_varlong(uint64_t value) {
   for (;;) {
      if (value & (~0x7Fu)) {
         write_byte((value & 0x7Fu) | 0x80u);
         value >>= 7;
         continue;
      }
      write_byte(value);
      break;
   }
}

int Writer::len_varint(int value) const {
   int result = 1;
   while (value & (~0x7Fu)) {
      ++result;
      value >>= 7;
   }
   return result;
}

void Writer::write_string(std::string_view s) {
   write_varint(s.size());
   stream << s;
}

void Writer::write_uuid_str(boost::uuids::uuid id) {
   write_string(boost::uuids::to_string(id));
}

void Writer::write_uuid(boost::uuids::uuid id) {
   stream.write((char *)id.data, 16);
}

void Writer::write_bytes(const char *data, size_t size) {
   stream.write(data, size);
}

void Writer::write_float(float value) {
   static_assert(sizeof(int32_t) == sizeof(float));
   auto value_be =
       boost::endian::native_to_big(*reinterpret_cast<int32_t *>(&value));
   stream.write((char *)&value_be, sizeof(value_be));
}

void Writer::write_double(double value) {
   static_assert(sizeof(int64_t) == sizeof(double));
   auto value_be =
       boost::endian::native_to_big(*reinterpret_cast<int64_t *>(&value));
   stream.write((char *)&value_be, sizeof(value_be));
}

static void write_buff_size(uint8_t *buff, std::size_t size) {
   int pos = 0;
   for (;;) {
      if (size & (~0x7Fu)) {
         buff[pos++] = (size & 0x7Fu) | 0x80u;
         size >>= 7;
         continue;
      }
      buff[pos++] = size;
      break;
   }
}

std::tuple<uint8_t *, size_t> Writer::buff(std::size_t comp_thres) {
   stream.seekg(0, std::ios::end);
   std::size_t buff_size = stream.tellg();

   if (comp_thres > 0) {
      if (buff_size < comp_thres) {
         // compression threshold not reached, just write data
         // put zero after size to indicate not compressed
         int total_size_num_bytes = len_varint(buff_size + 1);
         int header_size = total_size_num_bytes + 1;
         auto buff = new uint8_t[header_size + buff_size];
         write_buff_size(buff, buff_size + 1);
         buff[total_size_num_bytes] = 0;
         stream.seekg(0, std::ios::beg);
         stream.read((char *)buff + header_size, buff_size);
         return std::tuple(buff, buff_size + header_size);
      }

      // reached compression threshold
      // compress the data, write total size, write uncompressed size
      // and write compressed data

      std::vector<char> compressed;
      stream.seekg(0, std::ios::beg);
      Utils::compress_zlib(compressed, stream);

      int decompressed_size_num_bytes = len_varint(buff_size);
      std::size_t total_size = decompressed_size_num_bytes + compressed.size();
      int total_size_num_bytes = len_varint(total_size);

      int header_size = total_size_num_bytes + decompressed_size_num_bytes;

      auto buff = new uint8_t[header_size + compressed.size()];

      write_buff_size(buff, total_size);
      write_buff_size(buff + total_size_num_bytes, buff_size);

      std::memcpy(buff + header_size, compressed.data(), compressed.size());

      return std::tuple(buff, header_size + compressed.size());
   }

   // no compression, no encryption
   // write size, write data

   int header_size = len_varint(buff_size);

   auto buff = new uint8_t[header_size + buff_size];
   write_buff_size(buff, buff_size);

   stream.seekg(0, std::ios::beg);
   stream.read((char *)buff + header_size, buff_size);

   return std::tuple(buff, buff_size + header_size);
}

std::ostream &Writer::raw_stream() { return stream; }

size_t Writer::peek_size() {
   stream.seekg(0, std::ios::end);
   auto size = stream.tellg();
   stream.seekg(0, std::ios::beg);
   return size;
}

} // namespace MineNet::Message
