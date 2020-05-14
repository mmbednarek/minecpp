#include "writer.h"
#include <boost/uuid/uuid_io.hpp>

namespace MineNet::Message {

Writer::Writer() {}

void Writer::write_byte(uint8_t value) {
   stream.write((char *)&value, sizeof(uint8_t));
}

void Writer::write_varint(int value) {
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

void Writer::write_string(std::string_view s) {
   write_varint(s.size());
   stream << s;
}

void Writer::write_uuid(boost::uuids::uuid id) {
   //   stream.write((char *)id.data, 16); unfortunetly not :/
   write_string(boost::uuids::to_string(id));
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

std::tuple<uint8_t *, size_t> Writer::buff() {
   stream.seekg(0, std::ios::end);
   int buff_size = stream.tellg();
   auto buff = new uint8_t[buff_size + 4];
   int pos = 0;

   int value = buff_size;
   for (;;) {
      if (value & (~0x7Fu)) {
         buff[pos++] = (value & 0x7Fu) | 0x80u;
         value >>= 7;
         continue;
      }
      buff[pos++] = value;
      break;
   }

   stream.seekg(0, std::ios::beg);
   stream.read((char *)buff + pos, buff_size);

   return std::tuple(buff, buff_size + pos);
}

} // namespace Packet
