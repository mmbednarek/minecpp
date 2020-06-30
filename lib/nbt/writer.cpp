#include "writer.h"

namespace NBT {

Writer::Writer(std::ostream &s) : stream(s) {}

void Writer::write_string(std::string_view name, std::string_view str) {
   put_byte(NBT::String);
   put_string(name);
   put_string(str);
}

void Writer::write_byte(std::string_view name, uint8_t byte) {
   put_byte(NBT::Byte);
   put_string(name);
   put_byte(byte);
}

void Writer::write_int(std::string_view name, int value) {
   put_byte(NBT::Int);
   put_string(name);
   put_big_endian(value);
}

void Writer::write_long(std::string_view name, long long value) {
   put_byte(NBT::Long);
   put_string(name);
   put_big_endian(value);
}

void Writer::put_byte(uint8_t b) { stream.write((char *)&b, sizeof(uint8_t)); }

void Writer::put_string(std::string_view s) {
   put_big_endian<short>(s.length());
   stream.write((char *)s.data(), s.length());
}

void Writer::begin_compound(std::string_view name) {
   put_byte(NBT::Compound);
   put_string(name);
}

void Writer::end_compound() { put_byte(0x00); }

void Writer::write_long_array(std::string_view name, const long *array,
                              size_t size) {
   put_byte(NBT::LongArray);
   put_string(name);
   put_big_endian<int32_t>(size);
   for (size_t i = 0; i < size; ++i) {
      put_big_endian<int64_t>(array[i]);
   }
}

void Writer::write_float(std::string_view name, float value) {
   static_assert(sizeof(float) == sizeof(uint32_t));

   put_byte(NBT::Float);
   put_string(name);
   uint32_t v = *reinterpret_cast<uint32_t *>(&value);
   put_big_endian(v);
}

void Writer::begin_list(std::string_view name, NBT::TagID tag,
                        int num_elements) {
   put_byte(NBT::List);
   put_string(name);
   put_byte(tag);
   put_big_endian(num_elements);
}

} // namespace NBT
