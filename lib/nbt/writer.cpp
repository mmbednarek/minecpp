#include "writer.h"

namespace NBT {

Writer::Writer(std::ostream &s) : stream(s) {}

void Writer::write_byte(uint8_t b) {
   stream.write((char *)&b, sizeof(uint8_t));
}
void Writer::write_string(std::string_view s) {
   write_int<short>(s.length());
   stream.write((char *)s.data(), s.length());
}

} // namespace NBT
