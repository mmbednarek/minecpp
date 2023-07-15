#include "net/login/Clientbound.schema.h"
#include <algorithm>

namespace minecpp::net::login::cb {

void Disconnect::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
   writer.write_string(this->reason);
}

Disconnect Disconnect::deserialize(::minecpp::network::message::Reader &reader) {
   Disconnect result;
   result.reason = reader.read_string();
   return result;
}

void EncryptionRequest::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   writer.write_string(this->server_id);
   writer.write_varint(static_cast<std::int32_t>(this->public_key.size()));
   for (const auto &value_0 : this->public_key) {
      writer.write_byte(value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->token.size()));
   for (const auto &value_0 : this->token) {
      writer.write_byte(value_0);
   }
}

EncryptionRequest EncryptionRequest::deserialize(::minecpp::network::message::Reader &reader) {
   EncryptionRequest result;
   result.server_id = reader.read_string();
   auto public_key_size = reader.read_varint();
   result.public_key.resize(static_cast<std::size_t>(public_key_size));
   std::generate(result.public_key.begin(), result.public_key.end(), [&reader]() {
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

void LoginProperty::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->key);
   writer.write_string(this->value);
   if (this->signature.has_value()) {
      writer.write_byte(1);
      writer.write_string((*this->signature));
   } else {
      writer.write_byte(0);
   }
}

LoginProperty LoginProperty::deserialize(::minecpp::network::message::Reader &reader) {
   LoginProperty result;
   result.key = reader.read_string();
   result.value = reader.read_string();
   const auto signature_has_value = reader.read_byte();
   if (signature_has_value) {
      result.signature = reader.read_string();
   }
   return result;
}

void LoginSuccess::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x02);
   writer.write_uuid(this->player_id);
   writer.write_string(this->username);
   writer.write_varint(static_cast<std::int32_t>(this->properties.size()));
   for (const auto &value_0 : this->properties) {
      value_0.serialize(writer);
   }
}

LoginSuccess LoginSuccess::deserialize(::minecpp::network::message::Reader &reader) {
   LoginSuccess result;
   result.player_id = reader.read_uuid();
   result.username = reader.read_string();
   auto properties_size = reader.read_varint();
   result.properties.resize(static_cast<std::size_t>(properties_size));
   std::generate(result.properties.begin(), result.properties.end(), [&reader]() {
      LoginProperty result;
      result = LoginProperty::deserialize(reader);
      return result;
   });
   return result;
}

void SetCompression::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x03);
   writer.write_varint(this->threshold);
}

SetCompression SetCompression::deserialize(::minecpp::network::message::Reader &reader) {
   SetCompression result;
   result.threshold = reader.read_varint();
   return result;
}

void PluginRequest::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x04);
   writer.write_varint(this->message_id);
   writer.write_string(this->channel);
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &value_0 : this->data) {
      writer.write_byte(value_0);
   }
}

PluginRequest PluginRequest::deserialize(::minecpp::network::message::Reader &reader) {
   PluginRequest result;
   result.message_id = reader.read_varint();
   result.channel = reader.read_string();
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