#include <minecpp/nbt/writer.h>

namespace minecpp::nbt {

Writer::Writer(std::ostream &s) : stream(s) {}

void Writer::write_string(std::string_view name, std::string_view str) {
   put_byte(static_cast<uint8_t>(TagId::String));
   put_string(name);
   put_string(str);
}

void Writer::write_byte_content(uint8_t byte) {
   put_byte(byte);
}

void Writer::write_byte(std::string_view name, uint8_t byte) {
   put_byte(static_cast<uint8_t>(TagId::Byte));
   put_string(name);
   put_byte(byte);
}

void Writer::write_short_content(short value) {
   put_big_endian(value);
}

void Writer::write_short(std::string_view name, short value) {
   put_byte(static_cast<uint8_t>(TagId::Short));
   put_string(name);
   put_big_endian(value);
}

void Writer::write_int_content(int value) {
   put_big_endian(value);
}

void Writer::write_int(std::string_view name, int value) {
   put_byte(static_cast<uint8_t>(TagId::Int));
   put_string(name);
   put_big_endian(value);
}

void Writer::write_long_content(long long int value) {
   put_big_endian(value);
}

void Writer::write_long(std::string_view name, long long value) {
   put_byte(static_cast<uint8_t>(TagId::Long));
   put_string(name);
   put_big_endian(value);
}

void Writer::put_byte(uint8_t b) { stream.write((char *) &b, sizeof(uint8_t)); }


void Writer::write_string_content(std::string_view str) {
   put_string(str);
}

void Writer::put_string(const std::string_view s) {
   put_big_endian<short>(s.length());
   stream.write((char *) s.data(), s.length());
}

void Writer::begin_compound(const std::string_view name) {
   put_byte(static_cast<uint8_t>(TagId::Compound));
   put_string(name);
}

void Writer::end_compound() { put_byte(0x00); }

void Writer::write_long_array(std::string_view name, const long *array,
                              size_t size) {
   put_byte(static_cast<uint8_t>(TagId::LongArray));
   put_string(name);
   put_big_endian<int32_t>(size);
   for (size_t i = 0; i < size; ++i) {
      put_big_endian<int64_t>(array[i]);
   }
}

void Writer::write_float_content(float value) {
   uint32_t v = *reinterpret_cast<uint32_t *>(&value);
   put_big_endian(v);
}

void Writer::write_float(std::string_view name, float value) {
   static_assert(sizeof(float) == sizeof(uint32_t));

   put_byte(static_cast<uint8_t>(TagId::Float));
   put_string(name);
   uint32_t v = *reinterpret_cast<uint32_t *>(&value);
   put_big_endian(v);
}

void Writer::write_double_content(float value) {
   uint32_t v = *reinterpret_cast<uint32_t *>(&value);
   put_big_endian(v);
}

void Writer::write_double(std::string_view name, double value) {
   static_assert(sizeof(double) == sizeof(uint64_t));

   put_byte(static_cast<uint8_t>(TagId::Double));
   put_string(name);
   uint64_t v = *reinterpret_cast<uint64_t *>(&value);
   put_big_endian(v);
}

void Writer::begin_list(std::string_view name, nbt::TagId tag,
                        int num_elements) {
   put_byte(static_cast<uint8_t>(TagId::List));
   put_string(name);
   put_byte(static_cast<uint8_t>(tag));
   put_big_endian(num_elements);
}

void Writer::begin_list_no_header(const nbt::TagId tag, const int num_elements) {
   put_byte(static_cast<uint8_t>(tag));
   put_big_endian(num_elements);
}

void Writer::write_bytes_content(const std::vector<uint8_t> &values) {
   put_big_endian<int32_t>(values.size());
   for (const auto &val : values) {
      put_big_endian<uint8_t>(val);
   }
}

void Writer::write_bytes(std::string_view name, const std::vector<uint8_t> &values) {
   put_byte(static_cast<uint8_t>(TagId::ByteArray));
   put_string(name);
   put_big_endian<int32_t>(values.size());
   for (const auto &val : values) {
      put_big_endian<uint8_t>(val);
   }
}

void Writer::write_ints_content(const std::vector<int> &values) {
   put_big_endian<int32_t>(values.size());
   for (const auto &val : values) {
      put_big_endian<uint8_t>(val);
   }
}

void Writer::write_ints(std::string_view name, const std::vector<int> &values) {
   put_byte(static_cast<uint8_t>(TagId::IntArray));
   put_string(name);
   put_big_endian<int32_t>(values.size());
   for (const auto &val : values) {
      put_big_endian<int>(val);
   }
}

void Writer::write_longs_content(const std::vector<int64_t> &values) {
   put_big_endian<int32_t>(values.size());
   for (const auto &val : values) {
      put_big_endian<int64_t>(val);
   }
}

void Writer::write_longs(std::string_view name, const std::vector<int64_t> &values) {
   put_byte(static_cast<uint8_t>(TagId::LongArray));
   put_string(name);
   put_big_endian<int32_t>(values.size());
   for (const auto &val : values) {
      put_big_endian<int64_t>(val);
   }
}

void Writer::write_header(TagId tag, std::string_view name) {
   put_byte(static_cast<uint8_t>(tag));
   put_string(name);
}

}// namespace minecpp::nbt
