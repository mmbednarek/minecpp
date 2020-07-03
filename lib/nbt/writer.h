#pragma once
#include "tag.h"
#include <boost/endian/conversion.hpp>
#include <cmath>
#include <mineutils/concepts.h>
#include <ostream>

namespace NBT {

class Writer {
 public:
   Writer(std::ostream &s);

   void begin_compound(std::string_view name);
   void end_compound();
   void write_long_array(std::string_view name, const long *array, size_t size);

   void write_byte(std::string_view name, uint8_t byte);
   void write_int(std::string_view name, int value);
   void write_string(std::string_view name, std::string_view str);
   void write_float(std::string_view name, float value);
   void write_long(std::string_view name, long long value);
   void begin_list(std::string_view name, NBT::TagID tag, int num_elements);

 private:
   void put_byte(uint8_t b);
   void put_string(std::string_view s);
   template <typename I> void put_big_endian(I v) {
      v = boost::endian::native_to_big(v);
      stream.write((char *)&v, sizeof(I));
   }

   std::ostream &stream;
};

} // namespace NBT
