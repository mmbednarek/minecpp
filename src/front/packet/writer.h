#pragma once
#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>
#include <boost/uuid/uuid.hpp>
#include <sstream>
#include <tuple>
#include "../protocol/handler.h"

namespace Front {

class Connection;

namespace Packet {

class Writer {
 public:
   explicit Writer(Connection &conn);
   void write_byte(uint8_t value);
   void write_varint(int value);
   void write_string(std::string_view s);
   void write_uuid(boost::uuids::uuid id);
   void write_double(double d);
   void send();
   void send_and_read(Protocol::Handler& h);
   void send_and_disconnect();
   Connection &connection();

   template <typename T> void write_big_endian(T value) {
      value = boost::endian::native_to_big(value);
      stream.write((char *)&value, sizeof(T));
   }

 private:
   std::tuple<uint8_t *, size_t> buff();
   std::stringstream stream;
   Connection &conn;
};

} // namespace Packet

} // namespace Front
