#include "net/login/Serverbound.schema.h"
#include <algorithm>

namespace minecpp::net::login::sb {

void LoginStart::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
   writer.write_string(this->name);
   if (this->player_id.has_value()) {
      writer.write_byte(1);
      writer.write_uuid((*this->player_id));
   } else {
      writer.write_byte(0);
   }
}

LoginStart LoginStart::deserialize(::minecpp::network::message::Reader &reader) {
   LoginStart result;
   result.name = reader.read_string();
   const auto player_id_has_value = reader.read_byte();
   if (player_id_has_value) {
      result.player_id = reader.read_uuid();
   }
   return result;
}

void EncryptionResponse::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   writer.write_varint(static_cast<std::int32_t>(this->shared_secret.size()));
   for (const auto &value_0 : this->shared_secret) {
      writer.write_byte(value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->token.size()));
   for (const auto &value_0 : this->token) {
      writer.write_byte(value_0);
   }
}

EncryptionResponse EncryptionResponse::deserialize(::minecpp::network::message::Reader &reader) {
   EncryptionResponse result;
   auto shared_secret_size = reader.read_varint();
   result.shared_secret.resize(static_cast<std::size_t>(shared_secret_size));
   std::generate(result.shared_secret.begin(), result.shared_secret.end(), [&reader]() {
      std::uint8_t result;
      result = reader.read_byte();
      return result;
   });
   auto token_size = reader.read_varint();
   result.token.resize(static_cast<std::size_t>(token_size));
   std::generate(result.token.begin(), result.token.end(), [&reader]() {
      std::uint8_t result;
      result = reader.read_byte();
      return result;
   });
   return result;
}

void PluginResponse::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x02);
   writer.write_varint(this->message_id);
   writer.write_sbyte(this->is_successful);
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &value_0 : this->data) {
      writer.write_byte(value_0);
   }
}

PluginResponse PluginResponse::deserialize(::minecpp::network::message::Reader &reader) {
   PluginResponse result;
   result.message_id = reader.read_varint();
   result.is_successful = reader.read_sbyte();
   auto data_size = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      std::uint8_t result;
      result = reader.read_byte();
      return result;
   });
   return result;
}

}