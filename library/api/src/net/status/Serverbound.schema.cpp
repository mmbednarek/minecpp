#include "minecpp/network/NetworkUtil.h"
#include "net/status/Serverbound.schema.h"
#include <algorithm>

namespace minecpp::net::status::sb {

void Status::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
}

Status Status::deserialize(::minecpp::network::message::Reader &/*reader*/) {
   Status result;
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