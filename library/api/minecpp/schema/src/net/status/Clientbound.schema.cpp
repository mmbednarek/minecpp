#include "net/status/Clientbound.schema.h"
#include <algorithm>

namespace minecpp::net::status::cb {

void Status::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
   writer.write_string(this->status);
}

Status Status::deserialize(::minecpp::network::message::Reader &reader) {
   Status result;
   result.status = reader.read_string();
   return result;
}

void Ping::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   writer.write_big_endian(this->payload);
}

Ping Ping::deserialize(::minecpp::network::message::Reader &reader) {
   Ping result;
   result.payload = reader.read_big_endian<std::uint64_t>();
   return result;
}

}