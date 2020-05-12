#include "reader.h"
#include <boost/endian/conversion.hpp>

namespace Packet {

Reader::Reader(std::istream &s) : s(s) {}

uint8_t Reader::read_byte() {
   uint8_t result;
   s.read((char *)&result, sizeof(uint8_t));
   return result;
}

int Reader::read_varint() {
   uint32_t result = 0u;
   uint32_t shift = 0u;

   for (;;) {
      uint8_t b = read_byte();
      if (b & 0x80u) {
         result |= (b & 0x7Fu) << shift;
         shift += 7u;
         continue;
      }
      result |= b << shift;
      break;
   }
   return result;
}

std::string Reader::read_string() {
   int size = read_varint();
   char buff[size];
   s.read(buff, size);
   return std::string(buff, size);
}

} // namespace Packet
