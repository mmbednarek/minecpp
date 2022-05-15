#pragma once
#include <boost/endian/conversion.hpp>
#include <cassert>
#include <istream>
#include <vector>

namespace minecpp::util {

class Reader
{
 public:
   explicit Reader(std::istream &s);

   template<typename T>
   [[nodiscard]] T read_static(T def_value) const
   {
      T t = def_value;
      stream.read((char *) &t, sizeof(T));
      return t;
   }

   template<typename T>
   [[nodiscard]] T read_bswap() const
   {
      T v;
      stream.read((char *) &v, sizeof(T));
      v = boost::endian::big_to_native(v);
      return v;
   }

   template<typename T>
   [[nodiscard]] std::vector<T> read_int_list() const
   {
      auto size = read_bswap<int>();
      std::vector<T> result(size);
      for (int i = 0; i < size; i++) { result[i] = read_bswap<T>(); }
      return result;
   }

   [[nodiscard]] float read_float() const;
   [[nodiscard]] double read_double() const;
   [[nodiscard]] std::string read_string() const;
   [[nodiscard]] std::vector<uint8_t> read_byte_vec() const;

   std::istream &get_stream();

 private:
   std::istream &stream;
};
}// namespace minecpp::util
