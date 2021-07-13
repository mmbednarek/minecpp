#pragma once
#include "tag.h"
#include <boost/endian/conversion.hpp>
#include <cmath>
#include <minecpp/util/concepts.h>
#include <ostream>

namespace minecpp::nbt {

class Writer {
 public:
   Writer(std::ostream &s);

   void begin_compound(std::string_view name);
   void end_compound();
   void write_long_array(std::string_view name, const long *array, size_t size);

   void write_header(TagId tag, std::string_view name);

   void write_byte_content(uint8_t byte);
   void write_short_content(short value);
   void write_int_content(int value);
   void write_string_content(std::string_view str);
   void write_float_content(float value);
   void write_double_content(float value);
   void write_long_content(int64_t value);
   void write_bytes_content(const std::vector<uint8_t> &values);
   void write_ints_content(const std::vector<int> &values);
   void write_longs_content(const std::vector<int64_t> &values);

   void write_byte(std::string_view name, uint8_t byte);
   void write_short(std::string_view name, short value);
   void write_int(std::string_view name, int value);
   void write_string(std::string_view name, std::string_view str);
   void write_float(std::string_view name, float value);
   void write_double(std::string_view name, double value);
   void write_long(std::string_view name, int64_t value);
   void write_bytes(std::string_view name, const std::vector<uint8_t> &values);
   void write_ints(std::string_view name, const std::vector<int> &values);
   void write_longs(std::string_view name, const std::vector<int64_t> &values);
   void begin_list(std::string_view name, nbt::TagId tag, int num_elements);
   void begin_list_no_header(nbt::TagId tag, int num_elements);

 private:
   void put_byte(uint8_t b);
   void put_string(std::string_view s);
   template<typename I>
   void put_big_endian(I v) {
      v = boost::endian::native_to_big(v);
      stream.write((char *) &v, sizeof(I));
   }

   std::ostream &stream;
};

}// namespace minecpp::nbt
