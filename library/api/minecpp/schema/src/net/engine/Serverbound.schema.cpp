#include "minecpp/network/NetworkUtil.h"
#include "net/engine/Serverbound.schema.h"
#include <algorithm>

namespace minecpp::net::engine::sb {

void AcceptPlayer::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
   writer.write_uuid(this->player_id);
   writer.write_string(this->name);
}

AcceptPlayer AcceptPlayer::deserialize(::minecpp::network::message::Reader &reader) {
   AcceptPlayer result;
   result.player_id = reader.read_uuid();
   result.name = reader.read_string();
   return result;
}

void RemovePlayer::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   writer.write_uuid(this->player_id);
}

RemovePlayer RemovePlayer::deserialize(::minecpp::network::message::Reader &reader) {
   RemovePlayer result;
   result.player_id = reader.read_uuid();
   return result;
}

void PlayerMessage::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x02);
   writer.write_uuid(this->player_id);
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &data_value_0 : this->data) {
      writer.write_byte(data_value_0);
   }
}

PlayerMessage PlayerMessage::deserialize(::minecpp::network::message::Reader &reader) {
   PlayerMessage result;
   result.player_id = reader.read_uuid();
   auto data_size_0 = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size_0));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      return reader.read_byte();
   });
   return result;
}

}