#include "minecpp/network/NetworkUtil.h"
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
   for (const auto &[argument_signatures_key_0, argument_signatures_value_0] : this->argument_signatures) {
      writer.write_string(argument_signatures_key_0);
      writer.write_string(argument_signatures_value_0);
   }
   writer.write_varint(this->message_count);
   writer.write_varint(static_cast<std::int32_t>(this->acknowledged.size()));
   for (const auto &acknowledged_value_0 : this->acknowledged) {
      writer.write_big_endian(acknowledged_value_0);
   }
}

ChatCommand ChatCommand::deserialize(::minecpp::network::message::Reader &reader) {
   ChatCommand result;
   result.command = reader.read_string();
   result.timestamp = reader.read_big_endian<std::uint64_t>();
   result.salt = reader.read_big_endian<std::uint64_t>();
   const auto argument_signatures_map_size_0 = reader.read_varint();
   std::generate_n(std::inserter(result.argument_signatures, result.argument_signatures.begin()), static_cast<std::size_t>(argument_signatures_map_size_0), [&reader]() {
      std::string argument_signatures_key_0;
      argument_signatures_key_0 = reader.read_string();
      return std::make_pair(argument_signatures_key_0, reader.read_string());
   });
   result.message_count = reader.read_varint();
   auto acknowledged_size_0 = reader.read_varint();
   result.acknowledged.resize(static_cast<std::size_t>(acknowledged_size_0));
   std::generate(result.acknowledged.begin(), result.acknowledged.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   return result;
}

void ChatMessage::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x05);
   writer.write_string(this->message);
   writer.write_big_endian(this->timestamp);
   writer.write_big_endian(this->salt);
   if (this->signature.has_value()) {
      writer.write_byte(1);
      writer.write_string(*this->signature);
   } else {
      writer.write_byte(0);
   }
   writer.write_varint(this->message_count);
   writer.write_varint(static_cast<std::int32_t>(this->acknowledged.size()));
   for (const auto &acknowledged_value_0 : this->acknowledged) {
      writer.write_big_endian(acknowledged_value_0);
   }
}

ChatMessage ChatMessage::deserialize(::minecpp::network::message::Reader &reader) {
   ChatMessage result;
   result.message = reader.read_string();
   result.timestamp = reader.read_big_endian<std::uint64_t>();
   result.salt = reader.read_big_endian<std::uint64_t>();
   const auto signature_has_value_0 = reader.read_byte();
   if (signature_has_value_0) {
      result.signature = reader.read_string();
   }
   result.message_count = reader.read_varint();
   auto acknowledged_size_0 = reader.read_varint();
   result.acknowledged.resize(static_cast<std::size_t>(acknowledged_size_0));
   std::generate(result.acknowledged.begin(), result.acknowledged.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   return result;
}

void ClientCommand::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x07);
   writer.write_varint(this->action_id);
}

ClientCommand ClientCommand::deserialize(::minecpp::network::message::Reader &reader) {
   ClientCommand result;
   result.action_id = reader.read_varint();
   return result;
}

void ClientSettings::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x08);
   writer.write_string(this->locale);
   writer.write_byte(this->view_distance);
   writer.write_varint(this->chat_mode);
   writer.write_bool(this->are_colors_enabled);
   writer.write_byte(this->displayed_skin_parts);
   writer.write_sbyte(this->main_hand);
   writer.write_bool(this->is_text_filtering_enabled);
   writer.write_bool(this->are_players_listed);
}

ClientSettings ClientSettings::deserialize(::minecpp::network::message::Reader &reader) {
   ClientSettings result;
   result.locale = reader.read_string();
   result.view_distance = reader.read_byte();
   result.chat_mode = reader.read_varint();
   result.are_colors_enabled = reader.read_bool();
   result.displayed_skin_parts = reader.read_byte();
   result.main_hand = reader.read_sbyte();
   result.is_text_filtering_enabled = reader.read_bool();
   result.are_players_listed = reader.read_bool();
   return result;
}

void ClickWindow::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x0B);
   writer.write_byte(this->window_id);
   writer.write_varint(this->state_id);
   writer.write_big_endian(this->clicked_slot);
   writer.write_byte(this->button);
   writer.write_varint(this->mode);
   writer.write_varint(static_cast<std::int32_t>(this->slots.size()));
   for (const auto &[slots_key_0, slots_value_0] : this->slots) {
      writer.write_big_endian(slots_key_0);
      if (slots_value_0.has_value()) {
         writer.write_byte(1);
         slots_value_0->serialize(writer);
      } else {
         writer.write_byte(0);
      }
   }
   if (this->carried_item.has_value()) {
      writer.write_byte(1);
      this->carried_item->serialize(writer);
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
   const auto slots_map_size_0 = reader.read_varint();
   std::generate_n(std::inserter(result.slots, result.slots.begin()), static_cast<std::size_t>(slots_map_size_0), [&reader]() {
      std::uint16_t slots_key_0;
      slots_key_0 = reader.read_big_endian<std::uint16_t>();
      std::optional<net::Slot> slots_value_0;
      const auto slots_value_0_has_value_1 = reader.read_byte();
      if (slots_value_0_has_value_1) {
         slots_value_0 = net::Slot::deserialize(reader);
      }
      return std::make_pair(slots_key_0, slots_value_0);
   });
   const auto carried_item_has_value_0 = reader.read_byte();
   if (carried_item_has_value_0) {
      result.carried_item = net::Slot::deserialize(reader);
   }
   return result;
}

void CloseWindow::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x0C);
   writer.write_byte(this->window_id);
}

CloseWindow CloseWindow::deserialize(::minecpp::network::message::Reader &reader) {
   CloseWindow result;
   result.window_id = reader.read_byte();
   return result;
}

void PluginMessage::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x0D);
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
   network::write_vector3f(writer, this->position);
   writer.write_varint(this->hand);
}

InteractTarget InteractTarget::deserialize(::minecpp::network::message::Reader &reader) {
   InteractTarget result;
   result.position = network::read_vector3f(reader);
   result.hand = reader.read_varint();
   return result;
}

void Interact::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x10);
   writer.write_uvarint(this->entity_id);
   writer.write_varint(this->type);
   if (this->target.has_value()) {
      this->target->serialize(writer);
   }
   writer.write_bool(this->is_sneaking);
}

Interact Interact::deserialize(::minecpp::network::message::Reader &reader) {
   Interact result;
   result.entity_id = reader.read_uvarint();
   result.type = reader.read_varint();
   const auto target_has_value_0 = result.type == 2;
   if (target_has_value_0) {
      result.target = InteractTarget::deserialize(reader);
   }
   result.is_sneaking = reader.read_bool();
   return result;
}

void KeepAlive::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x12);
   writer.write_big_endian(this->time);
}

KeepAlive KeepAlive::deserialize(::minecpp::network::message::Reader &reader) {
   KeepAlive result;
   result.time = reader.read_big_endian<std::uint64_t>();
   return result;
}

void SetPlayerPosition::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x14);
   network::write_vector3(writer, this->position);
   writer.write_bool(this->is_on_ground);
}

SetPlayerPosition SetPlayerPosition::deserialize(::minecpp::network::message::Reader &reader) {
   SetPlayerPosition result;
   result.position = network::read_vector3(reader);
   result.is_on_ground = reader.read_bool();
   return result;
}

void SetPlayerPositionAndRotation::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x15);
   network::write_vector3(writer, this->position);
   writer.write_float(this->yaw);
   writer.write_float(this->pitch);
   writer.write_bool(this->is_on_ground);
}

SetPlayerPositionAndRotation SetPlayerPositionAndRotation::deserialize(::minecpp::network::message::Reader &reader) {
   SetPlayerPositionAndRotation result;
   result.position = network::read_vector3(reader);
   result.yaw = reader.read_float();
   result.pitch = reader.read_float();
   result.is_on_ground = reader.read_bool();
   return result;
}

void SetPlayerRotation::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x16);
   writer.write_float(this->yaw);
   writer.write_float(this->pitch);
   writer.write_bool(this->is_on_ground);
}

SetPlayerRotation SetPlayerRotation::deserialize(::minecpp::network::message::Reader &reader) {
   SetPlayerRotation result;
   result.yaw = reader.read_float();
   result.pitch = reader.read_float();
   result.is_on_ground = reader.read_bool();
   return result;
}

void SetIsPlayerOnGround::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x17);
   writer.write_bool(this->is_on_ground);
}

SetIsPlayerOnGround SetIsPlayerOnGround::deserialize(::minecpp::network::message::Reader &reader) {
   SetIsPlayerOnGround result;
   result.is_on_ground = reader.read_bool();
   return result;
}

void PlayerDigging::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x1D);
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
   writer.write_byte(0x1E);
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
   network::write_vector3f(writer, this->cursor_position);
   writer.write_bool(this->is_inside_block);
   writer.write_varint(this->sequence_id);
}

UseItemOn UseItemOn::deserialize(::minecpp::network::message::Reader &reader) {
   UseItemOn result;
   result.hand = reader.read_varint();
   result.position = reader.read_big_endian<std::uint64_t>();
   result.facing = reader.read_varint();
   result.cursor_position = network::read_vector3f(reader);
   result.is_inside_block = reader.read_bool();
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