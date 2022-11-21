#pragma once
#include <boost/endian/conversion.hpp>
#include <boost/uuid/uuid.hpp>
#include <minecpp/container/BasicBuffer.h>
#include <sstream>
#include <tuple>
#include <vector>

namespace minecpp::network::message {

int len_varint(int value);

class Writer
{
 public:
   explicit Writer();

   void write_byte(uint8_t value);
   void write_short(int16_t value);
   void write_long(uint64_t value);
   void write_varint(uint32_t value);
   void write_varlong(uint64_t value);
   void write_string(std::string_view s);
   void write_uuid_str(boost::uuids::uuid id);
   void write_uuid(boost::uuids::uuid id);
   void write_float(float value);
   void write_double(double d);
   void write_bytes(const char *data, std::size_t size);
   void write_from(Writer &other);

   std::tuple<uint8_t *, size_t> buff(std::size_t comp_thres);

   template<typename T>
   void write_big_endian(T value);
   template<typename I>
   void write_big_endian_array(std::vector<I> vec);
   template<typename I>
   void write_big_endian_array(I *data, std::size_t size);

   size_t peek_size();

   [[nodiscard]] std::ostream &raw_stream();

 private:
   std::stringstream stream;
};

template<typename T>
void Writer::write_big_endian(T value)
{
   value = boost::endian::native_to_big(value);
   stream.write((char *) &value, sizeof(T));
}

template<typename I>
void Writer::write_big_endian_array(std::vector<I> vec)
{
   write_varint(vec.size());
   for (auto const &v : vec) {
      write_big_endian(v);
   }
}

template<typename I>
void Writer::write_big_endian_array(I *data, std::size_t size)
{
   write_varint(size);
   for (std::size_t i = 0; i < size; ++i) {
      write_big_endian(data[i]);
   }
}

}// namespace minecpp::network::message
