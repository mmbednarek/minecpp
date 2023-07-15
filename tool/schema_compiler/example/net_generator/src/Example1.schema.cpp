#include "Example1.schema.h"
#include <algorithm>

namespace minecpp::example1 {

void Item::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->name);
   writer.write_big_endian(this->count);
   this->props.serialize(writer.raw_stream(), "");
}

Item Item::deserialize(::minecpp::network::message::Reader &reader) {
   Item result;
   result.name = reader.read_string();
   result.count = reader.read_big_endian<std::int16_t>();
   result.props = nbt::Properties::deserialize(reader.raw_stream());
   return result;
}

void Person::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   writer.write_string(this->name);
   writer.write_string(this->surname);
   writer.write_varint(this->age);
   writer.write_varint(static_cast<std::int32_t>(this->inventory.size()));
   for (const auto &value_0 : this->inventory) {
      writer.write_varint(static_cast<std::int32_t>(value_0.size()));
      for (const auto &value_1 : value_0) {
         value_1.serialize(writer);
      }
   }
   writer.write_big_endian(this->dimension_types);
   writer.write_uuid(this->foo);
   writer.write_varint(static_cast<std::int32_t>(this->opts.index()));
   switch (this->opts.index()) {
   case 0: {
      writer.write_float(std::get<0>(this->opts));
      break;
   }
   case 1: {
      writer.write_big_endian(std::get<1>(this->opts));
      break;
   }
   case 2: {
      std::get<2>(this->opts).serialize(writer);
      break;
   }
   default: 
      throw std::runtime_error("invalid variant");
   }
   for (const auto &[key_0, value_0] : this->more) {
      writer.write_byte(key_0);
      writer.write_string(value_0);
   }
   writer.write_byte(0xFF);
}

Person Person::deserialize(::minecpp::network::message::Reader &reader) {
   Person result;
   result.name = reader.read_string();
   result.surname = reader.read_string();
   result.age = reader.read_varint();
   auto inventory_size = reader.read_varint();
   result.inventory.resize(static_cast<std::size_t>(inventory_size));
   std::generate(result.inventory.begin(), result.inventory.end(), [&reader]() {
      std::vector<Item> result;
      auto result_size = reader.read_varint();
      result.resize(static_cast<std::size_t>(result_size));
      std::generate(result.begin(), result.end(), [&reader]() {
         Item result;
         result = Item::deserialize(reader);
         return result;
      });
      return result;
   });
   result.dimension_types = reader.read_big_endian<std::int32_t>();
   result.foo = reader.read_uuid();
   auto opts_index = reader.read_varint();
   switch (opts_index) {
   case 0: {
      result.opts = reader.read_float();
      break;
   }
   case 1: {
      result.opts = reader.read_big_endian<std::int32_t>();
      break;
   }
   case 2: {
      result.opts = Item::deserialize(reader);
      break;
   }
   default: 
      throw std::runtime_error("invalid variant");
   }
   for (; ; ) {
      std::uint8_t key_result;
      key_result = reader.read_byte();
      if (key_result == 0xFF) {
         break;
      }
      std::string value_result;
      value_result = reader.read_string();
      result.more[key_result] = std::move(value_result);
   }
   return result;
}

void Car::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x02);
   writer.write_string(this->brand);
   writer.write_string(this->vin);
   writer.write_big_endian(this->mileage);
}

Car Car::deserialize(::minecpp::network::message::Reader &reader) {
   Car result;
   result.brand = reader.read_string();
   result.vin = reader.read_string();
   result.mileage = reader.read_big_endian<std::int64_t>();
   return result;
}

void PlayerProperty::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->key);
   writer.write_string(this->value);
   if (this->signature.has_value()) {
      writer.write_byte(1);
      writer.write_string((*this->signature));
   } else {
      writer.write_byte(0);
   }
}

PlayerProperty PlayerProperty::deserialize(::minecpp::network::message::Reader &reader) {
   PlayerProperty result;
   result.key = reader.read_string();
   result.value = reader.read_string();
   const auto signature_has_value = reader.read_byte();
   if (signature_has_value) {
      result.signature = reader.read_string();
   }
   return result;
}

void ActionAddPlayer::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->name);
   writer.write_varint(static_cast<std::int32_t>(this->properties.size()));
   for (const auto &value_0 : this->properties) {
      value_0.serialize(writer);
   }
}

ActionAddPlayer ActionAddPlayer::deserialize(::minecpp::network::message::Reader &reader) {
   ActionAddPlayer result;
   result.name = reader.read_string();
   auto properties_size = reader.read_varint();
   result.properties.resize(static_cast<std::size_t>(properties_size));
   std::generate(result.properties.begin(), result.properties.end(), [&reader]() {
      PlayerProperty result;
      result = PlayerProperty::deserialize(reader);
      return result;
   });
   return result;
}

void PlayerChatSignature::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_uuid(this->chat_session_id);
   writer.write_big_endian(this->public_key_expiry);
   writer.write_string(this->public_key);
   writer.write_string(this->signature);
}

PlayerChatSignature PlayerChatSignature::deserialize(::minecpp::network::message::Reader &reader) {
   PlayerChatSignature result;
   result.chat_session_id = reader.read_uuid();
   result.public_key_expiry = reader.read_big_endian<std::uint64_t>();
   result.public_key = reader.read_string();
   result.signature = reader.read_string();
   return result;
}

void ActionInitializeChat::serialize(::minecpp::network::message::Writer &writer) const {
   if (this->chat_signature.has_value()) {
      writer.write_byte(1);
      (*this->chat_signature).serialize(writer);
   } else {
      writer.write_byte(0);
   }
}

ActionInitializeChat ActionInitializeChat::deserialize(::minecpp::network::message::Reader &reader) {
   ActionInitializeChat result;
   const auto chat_signature_has_value = reader.read_byte();
   if (chat_signature_has_value) {
      result.chat_signature = PlayerChatSignature::deserialize(reader);
   }
   return result;
}

void ActionSetGameMode::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(this->game_mode);
}

ActionSetGameMode ActionSetGameMode::deserialize(::minecpp::network::message::Reader &reader) {
   ActionSetGameMode result;
   result.game_mode = reader.read_varint();
   return result;
}

void ActionSetIsListed::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_sbyte(this->is_listed);
}

ActionSetIsListed ActionSetIsListed::deserialize(::minecpp::network::message::Reader &reader) {
   ActionSetIsListed result;
   result.is_listed = reader.read_sbyte();
   return result;
}

void ActionSetLatency::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(this->ping);
}

ActionSetLatency ActionSetLatency::deserialize(::minecpp::network::message::Reader &reader) {
   ActionSetLatency result;
   result.ping = reader.read_varint();
   return result;
}

void ActionSetDisplayName::serialize(::minecpp::network::message::Writer &writer) const {
   if (this->display_name.has_value()) {
      writer.write_byte(1);
      writer.write_string((*this->display_name));
   } else {
      writer.write_byte(0);
   }
}

ActionSetDisplayName ActionSetDisplayName::deserialize(::minecpp::network::message::Reader &reader) {
   ActionSetDisplayName result;
   const auto display_name_has_value = reader.read_byte();
   if (display_name_has_value) {
      result.display_name = reader.read_string();
   }
   return result;
}

void PlayerInfoChange::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_uuid(this->player_id);
   if (this->add_player.has_value()) {
      writer.write_byte(1);
      (*this->add_player).serialize(writer);
   } else {
      writer.write_byte(0);
   }
   if (this->initialize_chat.has_value()) {
      writer.write_byte(1);
      (*this->initialize_chat).serialize(writer);
   } else {
      writer.write_byte(0);
   }
   if (this->set_game_mode.has_value()) {
      writer.write_byte(1);
      (*this->set_game_mode).serialize(writer);
   } else {
      writer.write_byte(0);
   }
   if (this->set_is_listed.has_value()) {
      writer.write_byte(1);
      (*this->set_is_listed).serialize(writer);
   } else {
      writer.write_byte(0);
   }
   if (this->set_latency.has_value()) {
      writer.write_byte(1);
      (*this->set_latency).serialize(writer);
   } else {
      writer.write_byte(0);
   }
   if (this->set_display_name.has_value()) {
      writer.write_byte(1);
      (*this->set_display_name).serialize(writer);
   } else {
      writer.write_byte(0);
   }
}

PlayerInfoChange PlayerInfoChange::deserialize(::minecpp::network::message::Reader &reader, std::uint32_t action_bits) {
   PlayerInfoChange result;
   result.player_id = reader.read_uuid();
   const auto add_player_has_value = (action_bits & 1u) != 0u;
   if (add_player_has_value) {
      result.add_player = ActionAddPlayer::deserialize(reader);
   }
   const auto initialize_chat_has_value = (action_bits & 2u) != 0u;
   if (initialize_chat_has_value) {
      result.initialize_chat = ActionInitializeChat::deserialize(reader);
   }
   const auto set_game_mode_has_value = (action_bits & 3u) != 0u;
   if (set_game_mode_has_value) {
      result.set_game_mode = ActionSetGameMode::deserialize(reader);
   }
   const auto set_is_listed_has_value = (action_bits & 4u) != 0u;
   if (set_is_listed_has_value) {
      result.set_is_listed = ActionSetIsListed::deserialize(reader);
   }
   const auto set_latency_has_value = (action_bits & 5u) != 0u;
   if (set_latency_has_value) {
      result.set_latency = ActionSetLatency::deserialize(reader);
   }
   const auto set_display_name_has_value = (action_bits & 6u) != 0u;
   if (set_display_name_has_value) {
      result.set_display_name = ActionSetDisplayName::deserialize(reader);
   }
   return result;
}

void UpdatePlayerInfo::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(36);
   writer.write_big_endian(this->action_bits);
   writer.write_varint(static_cast<std::int32_t>(this->actions.size()));
   for (const auto &value_0 : this->actions) {
      value_0.serialize(writer);
   }
}

UpdatePlayerInfo UpdatePlayerInfo::deserialize(::minecpp::network::message::Reader &reader) {
   UpdatePlayerInfo result;
   result.action_bits = reader.read_big_endian<std::uint32_t>();
   auto actions_size = reader.read_varint();
   result.actions.resize(static_cast<std::size_t>(actions_size));
   std::generate(result.actions.begin(), result.actions.end(), [action_bits=result.action_bits, &reader]() {
      PlayerInfoChange result;
      result = PlayerInfoChange::deserialize(reader, action_bits);
      return result;
   });
   return result;
}

}