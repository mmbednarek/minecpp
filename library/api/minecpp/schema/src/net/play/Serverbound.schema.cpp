#include "net/play/Serverbound.schema.h"
#include <algorithm>

namespace minecpp::net::play::sb {

void ConfirmTeleport::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
   writer.write_varint(this->teleport_id);
}

ConfirmTeleport ConfirmTeleport::deserialize(::minecpp::network::message::Reader &reader) {
   ConfirmTeleport result;
   result.teleport_id = reader.read_varint();
   return result;
}

void ChatCommand::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x04);
   writer.write_string(this->command);
   writer.write_big_endian(this->timestamp);
   writer.write_big_endian(this->salt);
   writer.write_varint(static_cast<std::int32_t>(this->argument_signatures.size()));
   for (const auto &[key_0, value_0] : this->argument_signatures) {
      writer.write_string(key_0);
      writer.write_string(value_0);
   }
   writer.write_sbyte(this->is_preview);
}

ChatCommand ChatCommand::deserialize(::minecpp::network::message::Reader &reader) {
   ChatCommand result;
   result.command = reader.read_string();
   result.timestamp = reader.read_big_endian<std::uint64_t>();
   result.salt = reader.read_big_endian<std::uint64_t>();
   const auto argument_signatures_map_size = reader.read_varint();
   std::generate_n(std::inserter(result.argument_signatures, result.argument_signatures.begin()), static_cast<std::size_t>(argument_signatures_map_size), [&reader]() {
      std::string key_result;
      std::string value_result;
      key_result = reader.read_string();
      value_result = reader.read_string();
      return std::make_pair(key_result, value_result);
   });
   result.is_preview = reader.read_sbyte();
   return result;
}

void ChatMessage::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x05);
   writer.write_string(this->message);
   writer.write_big_endian(this->timestamp);
   writer.write_big_endian(this->salt);
   writer.write_string(this->salt_data);
   writer.write_sbyte(this->is_preview);
}

ChatMessage ChatMessage::deserialize(::minecpp::network::message::Reader &reader) {
   ChatMessage result;
   result.message = reader.read_string();
   result.timestamp = reader.read_big_endian<std::uint64_t>();
   result.salt = reader.read_big_endian<std::uint64_t>();
   result.salt_data = reader.read_string();
   result.is_preview = reader.read_sbyte();
   return result;
}

void ClientCommand::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x06);
   writer.write_varint(this->action_id);
}

ClientCommand ClientCommand::deserialize(::minecpp::network::message::Reader &reader) {
   ClientCommand result;
   result.action_id = reader.read_varint();
   return result;
}

void ClientSettings::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x07);
   writer.write_string(this->locale);
   writer.write_byte(this->view_distance);
   writer.write_varint(this->chat_mode);
   writer.write_sbyte(this->are_colors_enabled);
   writer.write_byte(this->displayed_skin_parts);
   writer.write_sbyte(this->main_hand);
   writer.write_sbyte(this->is_text_filtering_enabled);
   writer.write_sbyte(this->are_players_listed);
}

ClientSettings ClientSettings::deserialize(::minecpp::network::message::Reader &reader) {
   ClientSettings result;
   result.locale = reader.read_string();
   result.view_distance = reader.read_byte();
   result.chat_mode = reader.read_varint();
   result.are_colors_enabled = reader.read_sbyte();
   result.displayed_skin_parts = reader.read_byte();
   result.main_hand = reader.read_sbyte();
   result.is_text_filtering_enabled = reader.read_sbyte();
   result.are_players_listed = reader.read_sbyte();
   return result;
}

void ClickWindow::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x0A);
   writer.write_byte(this->window_id);
   writer.write_varint(this->state_id);
   writer.write_big_endian(this->clicked_slot);
   writer.write_byte(this->button);
   writer.write_varint(this->mode);
   writer.write_varint(static_cast<std::int32_t>(this->slots.size()));
   for (const auto &[key_0, value_0] : this->slots) {
      writer.write_big_endian(key_0);
      if (value_0.has_value()) {
         writer.write_byte(1);
         (*value_0).serialize(writer);
      } else {
         writer.write_byte(0);
      }
   }
   if (this->carried_item.has_value()) {
      writer.write_byte(1);
      (*this->carried_item).serialize(writer);
   } else {
      writer.write_byte(0);
   }
}

ClickWindow ClickWindow::deserialize(::minecpp::network::message::Reader &reader) {
   ClickWindow result;
   result.window_id = reader.read_byte();
   result.state_id = reader.read_varint();
   result.clicked_slot = reader.read_big_endian<std::int16_t>();
   result.button = reader.read_byte();
   result.mode = reader.read_varint();
   const auto slots_map_size = reader.read_varint();
   std::generate_n(std::inserter(result.slots, result.slots.begin()), static_cast<std::size_t>(slots_map_size), [&reader]() {
      std::uint16_t key_result;
      std::optional<play::Slot> value_result;
      key_result = reader.read_big_endian<std::uint16_t>();
      const auto value_result_has_value = reader.read_byte();
      if (value_result_has_value) {
         value_result = play::Slot::deserialize(reader);
      }
      return std::make_pair(key_result, value_result);
   });
   const auto carried_item_has_value = reader.read_byte();
   if (carried_item_has_value) {
      result.carried_item = play::Slot::deserialize(reader);
   }
   return result;
}

void CloseWindow::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x0B);
   writer.write_byte(this->window_id);
}

CloseWindow CloseWindow::deserialize(::minecpp::network::message::Reader &reader) {
   CloseWindow result;
   result.window_id = reader.read_byte();
   return result;
}

void PluginMessage::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x0C);
   writer.write_string(this->channel);
   writer.write_string(this->data);
}

PluginMessage PluginMessage::deserialize(::minecpp::network::message::Reader &reader) {
   PluginMessage result;
   result.channel = reader.read_string();
   result.data = reader.read_string();
   return result;
}

void InteractTarget::serialize(::minecpp::network::message::Writer &writer) const {
   this->position.serialize(writer);
   writer.write_varint(this->hand);
}

InteractTarget InteractTarget::deserialize(::minecpp::network::message::Reader &reader) {
   InteractTarget result;
   result.position = play::Vector3f::deserialize(reader);
   result.hand = reader.read_varint();
   return result;
}

void Interact::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x0F);
   writer.write_varint(this->entity_id);
   writer.write_varint(this->type);
   if (this->target.has_value()) {
      writer.write_byte(1);
      (*this->target).serialize(writer);
   } else {
      writer.write_byte(0);
   }
   writer.write_sbyte(this->is_sneaking);
}

Interact Interact::deserialize(::minecpp::network::message::Reader &reader) {
   Interact result;
   result.entity_id = reader.read_varint();
   result.type = reader.read_varint();
   const auto target_has_value = result.type == 2;
   if (target_has_value) {
      result.target = InteractTarget::deserialize(reader);
   }
   result.is_sneaking = reader.read_sbyte();
   return result;
}

void KeepAlive::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x11);
   writer.write_big_endian(this->time);
}

KeepAlive KeepAlive::deserialize(::minecpp::network::message::Reader &reader) {
   KeepAlive result;
   result.time = reader.read_big_endian<std::uint64_t>();
   return result;
}

void SetPlayerPosition::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x13);
   this->position.serialize(writer);
   writer.write_sbyte(this->is_on_ground);
}

SetPlayerPosition SetPlayerPosition::deserialize(::minecpp::network::message::Reader &reader) {
   SetPlayerPosition result;
   result.position = play::Vector3::deserialize(reader);
   result.is_on_ground = reader.read_sbyte();
   return result;
}

void SetPlayerPositionAndRotation::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x14);
   this->position.serialize(writer);
   writer.write_float(this->yaw);
   writer.write_float(this->pitch);
   writer.write_sbyte(this->is_on_ground);
}

SetPlayerPositionAndRotation SetPlayerPositionAndRotation::deserialize(::minecpp::network::message::Reader &reader) {
   SetPlayerPositionAndRotation result;
   result.position = play::Vector3::deserialize(reader);
   result.yaw = reader.read_float();
   result.pitch = reader.read_float();
   result.is_on_ground = reader.read_sbyte();
   return result;
}

void SetPlayerRotation::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x15);
   writer.write_float(this->yaw);
   writer.write_float(this->pitch);
   writer.write_sbyte(this->is_on_ground);
}

SetPlayerRotation SetPlayerRotation::deserialize(::minecpp::network::message::Reader &reader) {
   SetPlayerRotation result;
   result.yaw = reader.read_float();
   result.pitch = reader.read_float();
   result.is_on_ground = reader.read_sbyte();
   return result;
}

void SetIsPlayerOnGround::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x16);
   writer.write_sbyte(this->is_on_ground);
}

SetIsPlayerOnGround SetIsPlayerOnGround::deserialize(::minecpp::network::message::Reader &reader) {
   SetIsPlayerOnGround result;
   result.is_on_ground = reader.read_sbyte();
   return result;
}

void PlayerDigging::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x1C);
   writer.write_varint(this->state);
   writer.write_big_endian(this->position);
   writer.write_sbyte(this->facing);
   writer.write_varint(this->sequence_id);
}

PlayerDigging PlayerDigging::deserialize(::minecpp::network::message::Reader &reader) {
   PlayerDigging result;
   result.state = reader.read_varint();
   result.position = reader.read_big_endian<std::uint64_t>();
   result.facing = reader.read_sbyte();
   result.sequence_id = reader.read_varint();
   return result;
}

void PlayerCommand::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x1D);
   writer.write_varint(this->entity_id);
   writer.write_varint(this->action_id);
   writer.write_varint(this->jump_boost);
}

PlayerCommand PlayerCommand::deserialize(::minecpp::network::message::Reader &reader) {
   PlayerCommand result;
   result.entity_id = reader.read_varint();
   result.action_id = reader.read_varint();
   result.jump_boost = reader.read_varint();
   return result;
}

void SetHeldItem::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x28);
   writer.write_big_endian(this->slot_id);
}

SetHeldItem SetHeldItem::deserialize(::minecpp::network::message::Reader &reader) {
   SetHeldItem result;
   result.slot_id = reader.read_big_endian<std::uint16_t>();
   return result;
}

void AnimateHand::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x2F);
   writer.write_varint(this->hand);
}

AnimateHand AnimateHand::deserialize(::minecpp::network::message::Reader &reader) {
   AnimateHand result;
   result.hand = reader.read_varint();
   return result;
}

void UseItemOn::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x31);
   writer.write_varint(this->hand);
   writer.write_big_endian(this->position);
   writer.write_varint(this->facing);
   this->cursor_position.serialize(writer);
   writer.write_sbyte(this->is_inside_block);
   writer.write_varint(this->sequence_id);
}

UseItemOn UseItemOn::deserialize(::minecpp::network::message::Reader &reader) {
   UseItemOn result;
   result.hand = reader.read_varint();
   result.position = reader.read_big_endian<std::uint64_t>();
   result.facing = reader.read_varint();
   result.cursor_position = play::Vector3f::deserialize(reader);
   result.is_inside_block = reader.read_sbyte();
   result.sequence_id = reader.read_varint();
   return result;
}

void UseItem::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x32);
   writer.write_varint(this->hand);
   writer.write_varint(this->sequence_id);
}

UseItem UseItem::deserialize(::minecpp::network::message::Reader &reader) {
   UseItem result;
   result.hand = reader.read_varint();
   result.sequence_id = reader.read_varint();
   return result;
}

}