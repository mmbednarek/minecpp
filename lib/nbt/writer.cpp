#include "writer.h"

namespace NBT {

Writer::Writer(std::ostream &s) : stream(s) {}

void Writer::write_byte(uint8_t b) {
   stream.write((char *)&b, sizeof(uint8_t));
}

void Writer::write_string(std::string_view s) {
   write_big_endian<short>(s.length());
   stream.write((char *)s.data(), s.length());
}

void Writer::begin_compound(std::string_view name) {
   write_byte(NBT::Compound);
   write_string(name);
}

void Writer::end_compound() {
   write_byte(0x00);
}

void Writer::write_long_array(std::string_view name, const long *array, size_t size) {
   write_byte(NBT::LongArray);
   write_string(name);
   write_big_endian<int32_t>(size);
   for (size_t i = 0; i < size; ++i) {
      write_big_endian<int64_t>(array[i]);
   }
}

} // namespace NBT
