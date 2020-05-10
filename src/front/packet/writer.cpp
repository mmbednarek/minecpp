#include "writer.h"
#include "../connection.h"

namespace Front::Packet {

Writer::Writer(Connection *conn) : conn(conn) {}

void Writer::write_byte(uint8_t value) {
   stream.write((char *)&value, sizeof(uint8_t));
}

void Writer::write_varint(int value) {
   for (;;) {
      uint8_t b;
      if (value & (~0x7Fu)) {
         write_byte((value & 0x7Fu) | 0x80u);
         value >>= 7;
         continue;
      }
      write_byte(value);
      break;
   }
}

void Writer::write_string(std::string_view s) {
   write_varint(s.size());
   stream << s;
}

std::tuple<uint8_t *, size_t> Writer::buff() {
   stream.seekg(0, std::ios::end);
   int buff_size = stream.tellg();
   auto buff = new uint8_t[buff_size + 4];
   int pos = 0;

   int value = buff_size;
   for (;;) {
      if (value & (~0x7Fu)) {
         buff[pos++] = (value & 0x7Fu) | 0x80u;
         value >>= 7;
         continue;
      }
      buff[pos++] = value;
      break;
   }

   stream.seekg(0, std::ios::beg);
   stream.read((char *)buff + pos, buff_size);

   return std::tuple(buff, buff_size + pos);
}

void Writer::disconnect() { conn->disconnect(); }

Connection &Writer::connection() { return *conn; }

void Writer::send() {
   auto bf = buff();
   conn->async_write(std::get<0>(bf), std::get<1>(bf));
}
void Writer::send_and_read(Protocol::Handler& h) {
   auto bf = buff();
   conn->async_write_then_read(std::get<0>(bf), std::get<1>(bf), h);
}
void Writer::send_and_disconnect() {
   auto bf = buff();
   conn->async_write_then_disconnect(std::get<0>(bf), std::get<1>(bf));
}

} // namespace Front::Packet
