#pragma once
#include <boost/endian/conversion.hpp>
#include <boost/uuid/uuid.hpp>
#include <sstream>
#include <tuple>

namespace Packet {

class Writer {
 public:
   explicit Writer();

   void write_byte(uint8_t value);
   void write_varint(int value);
   void write_string(std::string_view s);
   void write_uuid(boost::uuids::uuid id);
   void write_float(float value);
   void write_double(double d);
   std::tuple<uint8_t *, size_t> buff();

   template <typename T> void write_big_endian(T value) {
      value = boost::endian::native_to_big(value);
      stream.write((char *)&value, sizeof(T));
   }

 private:
   std::stringstream stream;
};

} // namespace Packet
