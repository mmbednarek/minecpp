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

   void write_byte(uint8_t b);
   void write_string(std::string_view s);

   template <typename I> void write_int(I v) {
      v = boost::endian::native_to_big(v);
      stream.write((char *)&v, sizeof(I));
   }

   void write_packed_ints(std::string_view name, Indexable auto &values,
                          std::size_t len, int bits) {
      if ((len * bits) % 64 != 0)
         throw std::runtime_error("invalid bits or array length");

      write_byte(TagID::LongArray);
      write_string(name);

      int num_longs = (int)(len * bits) / 64;
      write_int(num_longs);

      int i = 0;
      uint16_t trail_size = 0;
      uint64_t trail = 0;

      for (int l = 0; l < num_longs; ++l) {
         uint64_t result = 0;

         if (trail_size > 0) {
            result |= trail >> (bits - trail_size);
         }

         uint8_t shift;
         for (shift = trail_size; shift + bits <= 64; shift += bits) {
            result |= ((uint64_t) values[i++]) << shift;
         }

         trail_size = shift + bits - 64;
         if (trail_size != bits) {
            trail = values[i++];
            result |= trail << shift;
         } else {
            trail_size = 0;
         }

         write_int(result);
      }
   };

 private:
   std::ostream &stream;
};

} // namespace NBT
