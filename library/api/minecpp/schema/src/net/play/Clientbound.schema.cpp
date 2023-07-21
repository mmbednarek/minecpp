#include "net/play/Clientbound.schema.h"
#include <algorithm>

namespace minecpp::net::play::cb {

void BundleDelimiter::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
}

BundleDelimiter BundleDelimiter::deserialize(::minecpp::network::message::Reader &/*reader*/) {
   BundleDelimiter result;
   return result;
}

void SpawnEntity::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   writer.write_uvarint(this->entity_id);
   writer.write_uuid(this->unique_id);
   writer.write_varint(this->entity_type);
   this->position.serialize(writer);
   writer.write_byte(this->pitch);
   writer.write_byte(this->yaw);
   writer.write_byte(this->head_yaw);
   writer.write_varint(this->data);
   this->velocity.serialize(writer);
}

SpawnEntity SpawnEntity::deserialize(::minecpp::network::message::Reader &reader) {
   SpawnEntity result;
   result.entity_id = reader.read_uvarint();
   result.unique_id = reader.read_uuid();
   result.entity_type = reader.read_varint();
   result.position = play::Vector3::deserialize(reader);
   result.pitch = reader.read_byte();
   result.yaw = reader.read_byte();
   result.head_yaw = reader.read_byte();
   result.data = reader.read_varint();
   result.velocity = play::Vector3s::deserialize(reader);
   return result;
}

void SpawnExperienceOrb::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x02);
   writer.write_uvarint(this->entity_id);
   this->position.serialize(writer);
   writer.write_big_endian(this->xp_value);
}

SpawnExperienceOrb SpawnExperienceOrb::deserialize(::minecpp::network::message::Reader &reader) {
   SpawnExperienceOrb result;
   result.entity_id = reader.read_uvarint();
   result.position = play::Vector3::deserialize(reader);
   result.xp_value = reader.read_big_endian<std::int16_t>();
   return result;
}

void SpawnPlayer::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x03);
   writer.write_uvarint(this->entity_id);
   writer.write_uuid(this->player_id);
   this->position.serialize(writer);
   writer.write_byte(this->yaw);
   writer.write_byte(this->pitch);
}

SpawnPlayer SpawnPlayer::deserialize(::minecpp::network::message::Reader &reader) {
   SpawnPlayer result;
   result.entity_id = reader.read_uvarint();
   result.player_id = reader.read_uuid();
   result.position = play::Vector3::deserialize(reader);
   result.yaw = reader.read_byte();
   result.pitch = reader.read_byte();
   return result;
}

void AnimateEntity::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x04);
   writer.write_uvarint(this->entity_id);
   writer.write_byte(this->type);
}

AnimateEntity AnimateEntity::deserialize(::minecpp::network::message::Reader &reader) {
   AnimateEntity result;
   result.entity_id = reader.read_uvarint();
   result.type = reader.read_byte();
   return result;
}

void AcknowledgeBlockChanges::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x06);
   writer.write_uvarint(this->sequence_id);
}

AcknowledgeBlockChanges AcknowledgeBlockChanges::deserialize(::minecpp::network::message::Reader &reader) {
   AcknowledgeBlockChanges result;
   result.sequence_id = reader.read_uvarint();
   return result;
}

void BlockChange::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x0A);
   writer.write_big_endian(this->block_position);
   writer.write_varint(this->block_id);
}

BlockChange BlockChange::deserialize(::minecpp::network::message::Reader &reader) {
   BlockChange result;
   result.block_position = reader.read_big_endian<std::uint64_t>();
   result.block_id = reader.read_varint();
   return result;
}

void Difficulty::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x0C);
   writer.write_byte(this->difficulty);
   writer.write_sbyte(this->locked);
}

Difficulty Difficulty::deserialize(::minecpp::network::message::Reader &reader) {
   Difficulty result;
   result.difficulty = reader.read_byte();
   result.locked = reader.read_sbyte();
   return result;
}

void SetSlot::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x14);
   writer.write_byte(this->window_id);
   writer.write_varint(this->state_id);
   writer.write_big_endian(this->slot_id);
   if (this->slot.has_value()) {
      writer.write_byte(1);
      this->slot->serialize(writer);
   } else {
      writer.write_byte(0);
   }
}

SetSlot SetSlot::deserialize(::minecpp::network::message::Reader &reader) {
   SetSlot result;
   result.window_id = reader.read_byte();
   result.state_id = reader.read_varint();
   result.slot_id = reader.read_big_endian<std::int16_t>();
   const auto slot_has_value_0 = reader.read_byte();
   if (slot_has_value_0) {
      result.slot = play::Slot::deserialize(reader);
   }
   return result;
}

void PluginMessage::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x17);
   writer.write_string(this->key);
   writer.write_string(this->value);
}

PluginMessage PluginMessage::deserialize(::minecpp::network::message::Reader &reader) {
   PluginMessage result;
   result.key = reader.read_string();
   result.value = reader.read_string();
   return result;
}

void DamageEvent::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x18);
   writer.write_uvarint(this->entity_id);
   writer.write_varint(this->type_id);
   writer.write_uvarint(this->entity_cause_id);
   writer.write_uvarint(this->entity_direct_id);
   if (this->source_position.has_value()) {
      writer.write_byte(1);
      this->source_position->serialize(writer);
   } else {
      writer.write_byte(0);
   }
}

DamageEvent DamageEvent::deserialize(::minecpp::network::message::Reader &reader) {
   DamageEvent result;
   result.entity_id = reader.read_uvarint();
   result.type_id = reader.read_varint();
   result.entity_cause_id = reader.read_uvarint();
   result.entity_direct_id = reader.read_uvarint();
   const auto source_position_has_value_0 = reader.read_byte();
   if (source_position_has_value_0) {
      result.source_position = play::Vector3::deserialize(reader);
   }
   return result;
}

void Disconnect::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x1A);
   writer.write_string(this->reason);
}

Disconnect Disconnect::deserialize(::minecpp::network::message::Reader &reader) {
   Disconnect result;
   result.reason = reader.read_string();
   return result;
}

void EntityStatus::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x1C);
   writer.write_big_endian(this->entity_id);
   writer.write_sbyte(this->opcode);
}

EntityStatus EntityStatus::deserialize(::minecpp::network::message::Reader &reader) {
   EntityStatus result;
   result.entity_id = reader.read_big_endian<std::int32_t>();
   result.opcode = reader.read_sbyte();
   return result;
}

void UnloadChunk::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x1E);
   this->position.serialize(writer);
}

UnloadChunk UnloadChunk::deserialize(::minecpp::network::message::Reader &reader) {
   UnloadChunk result;
   result.position = play::Vector2i::deserialize(reader);
   return result;
}

void KeepAlive::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x23);
   writer.write_big_endian(this->time);
}

KeepAlive KeepAlive::deserialize(::minecpp::network::message::Reader &reader) {
   KeepAlive result;
   result.time = reader.read_big_endian<std::int64_t>();
   return result;
}

void BlockEntity::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(this->position_xz);
   writer.write_big_endian(this->y);
   writer.write_varint(this->type);
   this->data.serialize(writer.raw_stream(), "");
}

BlockEntity BlockEntity::deserialize(::minecpp::network::message::Reader &reader) {
   BlockEntity result;
   result.position_xz = reader.read_byte();
   result.y = reader.read_big_endian<std::int16_t>();
   result.type = reader.read_varint();
   result.data = nbt::block::BlockEntityData::deserialize(reader.raw_stream());
   return result;
}

void LightData::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(static_cast<std::int32_t>(this->sky_light_mask.size()));
   for (const auto &sky_light_mask_value_0 : this->sky_light_mask) {
      writer.write_big_endian(sky_light_mask_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->block_light_mask.size()));
   for (const auto &block_light_mask_value_0 : this->block_light_mask) {
      writer.write_big_endian(block_light_mask_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->empty_sky_light_mask.size()));
   for (const auto &empty_sky_light_mask_value_0 : this->empty_sky_light_mask) {
      writer.write_big_endian(empty_sky_light_mask_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->empty_block_light_mask.size()));
   for (const auto &empty_block_light_mask_value_0 : this->empty_block_light_mask) {
      writer.write_big_endian(empty_block_light_mask_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->sky_light.size()));
   for (const auto &sky_light_value_0 : this->sky_light) {
      writer.write_varint(static_cast<std::int32_t>(sky_light_value_0.size()));
      for (const auto &sky_light_value_0_value_1 : sky_light_value_0) {
         writer.write_byte(sky_light_value_0_value_1);
      }
   }
   writer.write_varint(static_cast<std::int32_t>(this->block_light.size()));
   for (const auto &block_light_value_0 : this->block_light) {
      writer.write_varint(static_cast<std::int32_t>(block_light_value_0.size()));
      for (const auto &block_light_value_0_value_1 : block_light_value_0) {
         writer.write_byte(block_light_value_0_value_1);
      }
   }
}

LightData LightData::deserialize(::minecpp::network::message::Reader &reader) {
   LightData result;
   auto sky_light_mask_size_0 = reader.read_varint();
   result.sky_light_mask.resize(static_cast<std::size_t>(sky_light_mask_size_0));
   std::generate(result.sky_light_mask.begin(), result.sky_light_mask.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   auto block_light_mask_size_0 = reader.read_varint();
   result.block_light_mask.resize(static_cast<std::size_t>(block_light_mask_size_0));
   std::generate(result.block_light_mask.begin(), result.block_light_mask.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   auto empty_sky_light_mask_size_0 = reader.read_varint();
   result.empty_sky_light_mask.resize(static_cast<std::size_t>(empty_sky_light_mask_size_0));
   std::generate(result.empty_sky_light_mask.begin(), result.empty_sky_light_mask.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   auto empty_block_light_mask_size_0 = reader.read_varint();
   result.empty_block_light_mask.resize(static_cast<std::size_t>(empty_block_light_mask_size_0));
   std::generate(result.empty_block_light_mask.begin(), result.empty_block_light_mask.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   auto sky_light_size_0 = reader.read_varint();
   result.sky_light.resize(static_cast<std::size_t>(sky_light_size_0));
   std::generate(result.sky_light.begin(), result.sky_light.end(), [&reader]() {
      std::vector<std::uint8_t> sky_light_result_0;
      auto sky_light_result_0_size_1 = reader.read_varint();
      sky_light_result_0.resize(static_cast<std::size_t>(sky_light_result_0_size_1));
      std::generate(sky_light_result_0.begin(), sky_light_result_0.end(), [&reader]() {
         return reader.read_byte();
      });
      return sky_light_result_0;
   });
   auto block_light_size_0 = reader.read_varint();
   result.block_light.resize(static_cast<std::size_t>(block_light_size_0));
   std::generate(result.block_light.begin(), result.block_light.end(), [&reader]() {
      std::vector<std::uint8_t> block_light_result_0;
      auto block_light_result_0_size_1 = reader.read_varint();
      block_light_result_0.resize(static_cast<std::size_t>(block_light_result_0_size_1));
      std::generate(block_light_result_0.begin(), block_light_result_0.end(), [&reader]() {
         return reader.read_byte();
      });
      return block_light_result_0;
   });
   return result;
}

void UpdateChunk::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x24);
   this->position.serialize(writer);
   this->heightmaps.serialize(writer.raw_stream(), "");
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &data_value_0 : this->data) {
      writer.write_byte(data_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->block_entities.size()));
   for (const auto &block_entities_value_0 : this->block_entities) {
      block_entities_value_0.serialize(writer);
   }
   this->light_data.serialize(writer);
}

UpdateChunk UpdateChunk::deserialize(::minecpp::network::message::Reader &reader) {
   UpdateChunk result;
   result.position = play::Vector2i::deserialize(reader);
   result.heightmaps = nbt::chunk::HeightmapsNet::deserialize(reader.raw_stream());
   auto data_size_0 = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size_0));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      return reader.read_byte();
   });
   auto block_entities_size_0 = reader.read_varint();
   result.block_entities.resize(static_cast<std::size_t>(block_entities_size_0));
   std::generate(result.block_entities.begin(), result.block_entities.end(), [&reader]() {
      return BlockEntity::deserialize(reader);
   });
   result.light_data = LightData::deserialize(reader);
   return result;
}

void UpdateLight::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x27);
   this->position.serialize(writer);
   this->light_data.serialize(writer);
}

UpdateLight UpdateLight::deserialize(::minecpp::network::message::Reader &reader) {
   UpdateLight result;
   result.position = play::Vector2vi::deserialize(reader);
   result.light_data = LightData::deserialize(reader);
   return result;
}

void DeathLocation::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->dimension);
   writer.write_big_endian(this->position);
}

DeathLocation DeathLocation::deserialize(::minecpp::network::message::Reader &reader) {
   DeathLocation result;
   result.dimension = reader.read_string();
   result.position = reader.read_big_endian<std::uint64_t>();
   return result;
}

void JoinGame::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x28);
   writer.write_big_endian(this->entity_id);
   writer.write_bool(this->is_hardcode);
   writer.write_sbyte(this->game_mode);
   writer.write_sbyte(this->previous_game_mode);
   writer.write_varint(static_cast<std::int32_t>(this->available_dimensions.size()));
   for (const auto &available_dimensions_value_0 : this->available_dimensions) {
      writer.write_string(available_dimensions_value_0);
   }
   this->dimension_codec.serialize(writer.raw_stream(), "");
   writer.write_string(this->dimension_name);
   writer.write_string(this->world_name);
   writer.write_big_endian(this->seed);
   writer.write_varint(this->max_players);
   writer.write_varint(this->view_distance);
   writer.write_varint(this->simulation_distance);
   writer.write_sbyte(this->reduced_debug_info);
   writer.write_bool(this->should_show_respawn_screen);
   writer.write_bool(this->is_debug);
   writer.write_bool(this->is_flat);
   if (this->death_location.has_value()) {
      writer.write_byte(1);
      this->death_location->serialize(writer);
   } else {
      writer.write_byte(0);
   }
   writer.write_varint(this->portal_cooldown);
}

JoinGame JoinGame::deserialize(::minecpp::network::message::Reader &reader) {
   JoinGame result;
   result.entity_id = reader.read_big_endian<std::uint32_t>();
   result.is_hardcode = reader.read_bool();
   result.game_mode = reader.read_sbyte();
   result.previous_game_mode = reader.read_sbyte();
   auto available_dimensions_size_0 = reader.read_varint();
   result.available_dimensions.resize(static_cast<std::size_t>(available_dimensions_size_0));
   std::generate(result.available_dimensions.begin(), result.available_dimensions.end(), [&reader]() {
      return reader.read_string();
   });
   result.dimension_codec = nbt::repository::Registry::deserialize(reader.raw_stream());
   result.dimension_name = reader.read_string();
   result.world_name = reader.read_string();
   result.seed = reader.read_big_endian<std::uint64_t>();
   result.max_players = reader.read_varint();
   result.view_distance = reader.read_varint();
   result.simulation_distance = reader.read_varint();
   result.reduced_debug_info = reader.read_sbyte();
   result.should_show_respawn_screen = reader.read_bool();
   result.is_debug = reader.read_bool();
   result.is_flat = reader.read_bool();
   const auto death_location_has_value_0 = reader.read_byte();
   if (death_location_has_value_0) {
      result.death_location = DeathLocation::deserialize(reader);
   }
   result.portal_cooldown = reader.read_varint();
   return result;
}

void EntityRelativeMove::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x2B);
   writer.write_uvarint(this->entity_id);
   this->difference.serialize(writer);
   writer.write_bool(this->is_on_ground);
}

EntityRelativeMove EntityRelativeMove::deserialize(::minecpp::network::message::Reader &reader) {
   EntityRelativeMove result;
   result.entity_id = reader.read_uvarint();
   result.difference = play::Vector3s::deserialize(reader);
   result.is_on_ground = reader.read_bool();
   return result;
}

void EntityMove::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x2C);
   writer.write_uvarint(this->entity_id);
   this->difference.serialize(writer);
   writer.write_byte(this->yaw);
   writer.write_byte(this->pitch);
   writer.write_bool(this->is_on_ground);
}

EntityMove EntityMove::deserialize(::minecpp::network::message::Reader &reader) {
   EntityMove result;
   result.entity_id = reader.read_uvarint();
   result.difference = play::Vector3s::deserialize(reader);
   result.yaw = reader.read_byte();
   result.pitch = reader.read_byte();
   result.is_on_ground = reader.read_bool();
   return result;
}

void EntityLook::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x2D);
   writer.write_uvarint(this->entity_id);
   writer.write_byte(this->yaw);
   writer.write_byte(this->pitch);
   writer.write_bool(this->is_on_ground);
}

EntityLook EntityLook::deserialize(::minecpp::network::message::Reader &reader) {
   EntityLook result;
   result.entity_id = reader.read_uvarint();
   result.yaw = reader.read_byte();
   result.pitch = reader.read_byte();
   result.is_on_ground = reader.read_bool();
   return result;
}

void PlayerAbilities::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x34);
   writer.write_byte(this->flags);
   writer.write_float(this->fly_speed);
   writer.write_float(this->field_of_view);
}

PlayerAbilities PlayerAbilities::deserialize(::minecpp::network::message::Reader &reader) {
   PlayerAbilities result;
   result.flags = reader.read_byte();
   result.fly_speed = reader.read_float();
   result.field_of_view = reader.read_float();
   return result;
}

void DisplayDeathScreen::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x38);
   writer.write_uvarint(this->victim_entity_id);
   writer.write_string(this->message);
}

DisplayDeathScreen DisplayDeathScreen::deserialize(::minecpp::network::message::Reader &reader) {
   DisplayDeathScreen result;
   result.victim_entity_id = reader.read_uvarint();
   result.message = reader.read_string();
   return result;
}

void RemovePlayerInfo::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x39);
   writer.write_varint(static_cast<std::int32_t>(this->player_ids.size()));
   for (const auto &player_ids_value_0 : this->player_ids) {
      writer.write_uuid(player_ids_value_0);
   }
}

RemovePlayerInfo RemovePlayerInfo::deserialize(::minecpp::network::message::Reader &reader) {
   RemovePlayerInfo result;
   auto player_ids_size_0 = reader.read_varint();
   result.player_ids.resize(static_cast<std::size_t>(player_ids_size_0));
   std::generate(result.player_ids.begin(), result.player_ids.end(), [&reader]() {
      return reader.read_uuid();
   });
   return result;
}

void PlayerProperty::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->key);
   writer.write_string(this->value);
   if (this->signature.has_value()) {
      writer.write_byte(1);
      writer.write_string(*this->signature);
   } else {
      writer.write_byte(0);
   }
}

PlayerProperty PlayerProperty::deserialize(::minecpp::network::message::Reader &reader) {
   PlayerProperty result;
   result.key = reader.read_string();
   result.value = reader.read_string();
   const auto signature_has_value_0 = reader.read_byte();
   if (signature_has_value_0) {
      result.signature = reader.read_string();
   }
   return result;
}

void ActionAddPlayer::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->name);
   writer.write_varint(static_cast<std::int32_t>(this->properties.size()));
   for (const auto &properties_value_0 : this->properties) {
      properties_value_0.serialize(writer);
   }
}

ActionAddPlayer ActionAddPlayer::deserialize(::minecpp::network::message::Reader &reader) {
   ActionAddPlayer result;
   result.name = reader.read_string();
   auto properties_size_0 = reader.read_varint();
   result.properties.resize(static_cast<std::size_t>(properties_size_0));
   std::generate(result.properties.begin(), result.properties.end(), [&reader]() {
      return PlayerProperty::deserialize(reader);
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
      this->chat_signature->serialize(writer);
   } else {
      writer.write_byte(0);
   }
}

ActionInitializeChat ActionInitializeChat::deserialize(::minecpp::network::message::Reader &reader) {
   ActionInitializeChat result;
   const auto chat_signature_has_value_0 = reader.read_byte();
   if (chat_signature_has_value_0) {
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
   writer.write_bool(this->is_listed);
}

ActionSetIsListed ActionSetIsListed::deserialize(::minecpp::network::message::Reader &reader) {
   ActionSetIsListed result;
   result.is_listed = reader.read_bool();
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
      writer.write_string(*this->display_name);
   } else {
      writer.write_byte(0);
   }
}

ActionSetDisplayName ActionSetDisplayName::deserialize(::minecpp::network::message::Reader &reader) {
   ActionSetDisplayName result;
   const auto display_name_has_value_0 = reader.read_byte();
   if (display_name_has_value_0) {
      result.display_name = reader.read_string();
   }
   return result;
}

void PlayerInfoChange::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_uuid(this->player_id);
   if (this->add_player.has_value()) {
      this->add_player->serialize(writer);
   }
   if (this->initialize_chat.has_value()) {
      this->initialize_chat->serialize(writer);
   }
   if (this->set_game_mode.has_value()) {
      this->set_game_mode->serialize(writer);
   }
   if (this->set_is_listed.has_value()) {
      this->set_is_listed->serialize(writer);
   }
   if (this->set_latency.has_value()) {
      this->set_latency->serialize(writer);
   }
   if (this->set_display_name.has_value()) {
      this->set_display_name->serialize(writer);
   }
}

PlayerInfoChange PlayerInfoChange::deserialize(::minecpp::network::message::Reader &reader, std::uint8_t action_bits) {
   PlayerInfoChange result;
   result.player_id = reader.read_uuid();
   const auto add_player_has_value_0 = (action_bits & 1u) != 0u;
   if (add_player_has_value_0) {
      result.add_player = ActionAddPlayer::deserialize(reader);
   }
   const auto initialize_chat_has_value_0 = (action_bits & 2u) != 0u;
   if (initialize_chat_has_value_0) {
      result.initialize_chat = ActionInitializeChat::deserialize(reader);
   }
   const auto set_game_mode_has_value_0 = (action_bits & 3u) != 0u;
   if (set_game_mode_has_value_0) {
      result.set_game_mode = ActionSetGameMode::deserialize(reader);
   }
   const auto set_is_listed_has_value_0 = (action_bits & 4u) != 0u;
   if (set_is_listed_has_value_0) {
      result.set_is_listed = ActionSetIsListed::deserialize(reader);
   }
   const auto set_latency_has_value_0 = (action_bits & 5u) != 0u;
   if (set_latency_has_value_0) {
      result.set_latency = ActionSetLatency::deserialize(reader);
   }
   const auto set_display_name_has_value_0 = (action_bits & 6u) != 0u;
   if (set_display_name_has_value_0) {
      result.set_display_name = ActionSetDisplayName::deserialize(reader);
   }
   return result;
}

void UpdatePlayerInfo::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x3A);
   writer.write_byte(this->action_bits);
   writer.write_varint(static_cast<std::int32_t>(this->actions.size()));
   for (const auto &actions_value_0 : this->actions) {
      actions_value_0.serialize(writer);
   }
}

UpdatePlayerInfo UpdatePlayerInfo::deserialize(::minecpp::network::message::Reader &reader) {
   UpdatePlayerInfo result;
   result.action_bits = reader.read_byte();
   auto actions_size_0 = reader.read_varint();
   result.actions.resize(static_cast<std::size_t>(actions_size_0));
   std::generate(result.actions.begin(), result.actions.end(), [action_bits=result.action_bits, &reader]() {
      return PlayerInfoChange::deserialize(reader, action_bits);
   });
   return result;
}

void PlayerPositionLook::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x3C);
   this->position.serialize(writer);
   writer.write_float(this->yaw);
   writer.write_float(this->pitch);
   writer.write_byte(this->flags);
   writer.write_varint(this->teleport_id);
}

PlayerPositionLook PlayerPositionLook::deserialize(::minecpp::network::message::Reader &reader) {
   PlayerPositionLook result;
   result.position = play::Vector3::deserialize(reader);
   result.yaw = reader.read_float();
   result.pitch = reader.read_float();
   result.flags = reader.read_byte();
   result.teleport_id = reader.read_varint();
   return result;
}

void RecipeGui::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_bool(this->is_open);
   writer.write_bool(this->is_filtering_craftable);
}

RecipeGui RecipeGui::deserialize(::minecpp::network::message::Reader &reader) {
   RecipeGui result;
   result.is_open = reader.read_bool();
   result.is_filtering_craftable = reader.read_bool();
   return result;
}

void RecipeList::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(static_cast<std::int32_t>(this->recipes.size()));
   for (const auto &recipes_value_0 : this->recipes) {
      writer.write_string(recipes_value_0);
   }
}

RecipeList RecipeList::deserialize(::minecpp::network::message::Reader &reader) {
   RecipeList result;
   auto recipes_size_0 = reader.read_varint();
   result.recipes.resize(static_cast<std::size_t>(recipes_size_0));
   std::generate(result.recipes.begin(), result.recipes.end(), [&reader]() {
      return reader.read_string();
   });
   return result;
}

void RecipeBook::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x3D);
   writer.write_varint(this->state);
   this->crafting_table.serialize(writer);
   this->furnace.serialize(writer);
   this->blaster.serialize(writer);
   this->smoker.serialize(writer);
   writer.write_varint(static_cast<std::int32_t>(this->recipes.size()));
   for (const auto &recipes_value_0 : this->recipes) {
      writer.write_string(recipes_value_0);
   }
   if (this->additional_recipes.has_value()) {
      this->additional_recipes->serialize(writer);
   }
}

RecipeBook RecipeBook::deserialize(::minecpp::network::message::Reader &reader) {
   RecipeBook result;
   result.state = reader.read_varint();
   result.crafting_table = RecipeGui::deserialize(reader);
   result.furnace = RecipeGui::deserialize(reader);
   result.blaster = RecipeGui::deserialize(reader);
   result.smoker = RecipeGui::deserialize(reader);
   auto recipes_size_0 = reader.read_varint();
   result.recipes.resize(static_cast<std::size_t>(recipes_size_0));
   std::generate(result.recipes.begin(), result.recipes.end(), [&reader]() {
      return reader.read_string();
   });
   const auto additional_recipes_has_value_0 = result.state == 0;
   if (additional_recipes_has_value_0) {
      result.additional_recipes = RecipeList::deserialize(reader);
   }
   return result;
}

void RemoveEntities::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x3E);
   writer.write_varint(static_cast<std::int32_t>(this->entity_ids.size()));
   for (const auto &entity_ids_value_0 : this->entity_ids) {
      writer.write_uvarint(entity_ids_value_0);
   }
}

RemoveEntities RemoveEntities::deserialize(::minecpp::network::message::Reader &reader) {
   RemoveEntities result;
   auto entity_ids_size_0 = reader.read_varint();
   result.entity_ids.resize(static_cast<std::size_t>(entity_ids_size_0));
   std::generate(result.entity_ids.begin(), result.entity_ids.end(), [&reader]() {
      return reader.read_uvarint();
   });
   return result;
}

void Respawn::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x41);
   writer.write_string(this->dimension_codec);
   writer.write_string(this->dimension_name);
   writer.write_big_endian(this->seed);
   writer.write_byte(this->game_mode);
   writer.write_sbyte(this->previous_game_mode);
   writer.write_bool(this->is_debug);
   writer.write_bool(this->is_flat);
   writer.write_byte(this->should_copy_metadata);
   if (this->death_location.has_value()) {
      writer.write_byte(1);
      this->death_location->serialize(writer);
   } else {
      writer.write_byte(0);
   }
   writer.write_varint(this->portal_cooldown);
}

Respawn Respawn::deserialize(::minecpp::network::message::Reader &reader) {
   Respawn result;
   result.dimension_codec = reader.read_string();
   result.dimension_name = reader.read_string();
   result.seed = reader.read_big_endian<std::uint64_t>();
   result.game_mode = reader.read_byte();
   result.previous_game_mode = reader.read_sbyte();
   result.is_debug = reader.read_bool();
   result.is_flat = reader.read_bool();
   result.should_copy_metadata = reader.read_byte();
   const auto death_location_has_value_0 = reader.read_byte();
   if (death_location_has_value_0) {
      result.death_location = DeathLocation::deserialize(reader);
   }
   result.portal_cooldown = reader.read_varint();
   return result;
}

void EntityHeadLook::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x42);
   writer.write_uvarint(this->entity_id);
   writer.write_byte(this->yaw);
}

EntityHeadLook EntityHeadLook::deserialize(::minecpp::network::message::Reader &reader) {
   EntityHeadLook result;
   result.entity_id = reader.read_uvarint();
   result.yaw = reader.read_byte();
   return result;
}

void MultiBlockChange::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x43);
   writer.write_big_endian(this->chunk_position);
   writer.write_varint(static_cast<std::int32_t>(this->block_changes.size()));
   for (const auto &block_changes_value_0 : this->block_changes) {
      writer.write_varlong(block_changes_value_0);
   }
}

MultiBlockChange MultiBlockChange::deserialize(::minecpp::network::message::Reader &reader) {
   MultiBlockChange result;
   result.chunk_position = reader.read_big_endian<std::uint64_t>();
   auto block_changes_size_0 = reader.read_varint();
   result.block_changes.resize(static_cast<std::size_t>(block_changes_size_0));
   std::generate(result.block_changes.begin(), result.block_changes.end(), [&reader]() {
      return reader.read_varlong();
   });
   return result;
}

void ChangeHeldItem::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x4D);
   writer.write_sbyte(this->item_index);
}

ChangeHeldItem ChangeHeldItem::deserialize(::minecpp::network::message::Reader &reader) {
   ChangeHeldItem result;
   result.item_index = reader.read_sbyte();
   return result;
}

void UpdateChunkPosition::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x4E);
   this->chunk_position.serialize(writer);
}

UpdateChunkPosition UpdateChunkPosition::deserialize(::minecpp::network::message::Reader &reader) {
   UpdateChunkPosition result;
   result.chunk_position = play::Vector2vi::deserialize(reader);
   return result;
}

void SetDefaultSpawnPosition::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x50);
   writer.write_big_endian(this->position);
   writer.write_float(this->angle);
}

SetDefaultSpawnPosition SetDefaultSpawnPosition::deserialize(::minecpp::network::message::Reader &reader) {
   SetDefaultSpawnPosition result;
   result.position = reader.read_big_endian<std::uint64_t>();
   result.angle = reader.read_float();
   return result;
}

void SetEntityMetadata::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x52);
   writer.write_uvarint(this->entity_id);
   for (const auto &[data_key_0, data_value_0] : this->data) {
      writer.write_byte(data_key_0);
      writer.write_varint(static_cast<std::int32_t>(data_value_0.index()));
      switch (data_value_0.index()) {
      case 0: {
         writer.write_sbyte(std::get<0>(data_value_0));
         break;
      }
      case 1: {
         writer.write_varint(std::get<1>(data_value_0));
         break;
      }
      case 2: {
         writer.write_varlong(std::get<2>(data_value_0));
         break;
      }
      case 3: {
         writer.write_float(std::get<3>(data_value_0));
         break;
      }
      case 4: {
         writer.write_string(std::get<4>(data_value_0));
         break;
      }
      case 5: {
         std::get<5>(data_value_0).serialize(writer);
         break;
      }
      case 6: {
         if (std::get<6>(data_value_0).has_value()) {
            writer.write_byte(1);
            std::get<6>(data_value_0)->serialize(writer);
         } else {
            writer.write_byte(0);
         }
         break;
      }
      case 7: {
         if (std::get<7>(data_value_0).has_value()) {
            writer.write_byte(1);
            std::get<7>(data_value_0)->serialize(writer);
         } else {
            writer.write_byte(0);
         }
         break;
      }
      default: 
         throw std::runtime_error("invalid variant");
      }
   }
   writer.write_byte(0xFF);
}

SetEntityMetadata SetEntityMetadata::deserialize(::minecpp::network::message::Reader &reader) {
   SetEntityMetadata result;
   result.entity_id = reader.read_uvarint();
   for (; ; ) {
      std::uint8_t data_key_0;
      data_key_0 = reader.read_byte();
      if (data_key_0 == 0xFF) {
         break;
      }
      std::variant<std::int8_t, std::int32_t, std::int64_t, float, std::string, play::Chat, std::optional<play::Chat>, std::optional<play::Slot>> data_value_0;
      auto data_value_0_index_1 = reader.read_varint();
      switch (data_value_0_index_1) {
      case 0: {
         data_value_0 = reader.read_sbyte();
         break;
      }
      case 1: {
         data_value_0 = reader.read_varint();
         break;
      }
      case 2: {
         data_value_0 = reader.read_varlong();
         break;
      }
      case 3: {
         data_value_0 = reader.read_float();
         break;
      }
      case 4: {
         data_value_0 = reader.read_string();
         break;
      }
      case 5: {
         data_value_0 = play::Chat::deserialize(reader);
         break;
      }
      case 6: {
         const auto data_value_0_item_1_has_value_2 = reader.read_byte();
         if (data_value_0_item_1_has_value_2) {
            data_value_0 = play::Chat::deserialize(reader);
         }
         break;
      }
      case 7: {
         const auto data_value_0_item_1_has_value_2 = reader.read_byte();
         if (data_value_0_item_1_has_value_2) {
            data_value_0 = play::Slot::deserialize(reader);
         }
         break;
      }
      default: 
         throw std::runtime_error("invalid variant");
      }
      result.data.emplace(data_key_0, data_value_0);
   }
   return result;
}

void SetEntityVelocity::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x54);
   writer.write_uvarint(this->entity_id);
   this->velocity.serialize(writer);
}

SetEntityVelocity SetEntityVelocity::deserialize(::minecpp::network::message::Reader &reader) {
   SetEntityVelocity result;
   result.entity_id = reader.read_uvarint();
   result.velocity = play::Vector3s::deserialize(reader);
   return result;
}

void SetEquipment::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x55);
   writer.write_uvarint(this->entity_id);
   writer.write_sbyte(this->slot_id);
   if (this->slot.has_value()) {
      writer.write_byte(1);
      this->slot->serialize(writer);
   } else {
      writer.write_byte(0);
   }
}

SetEquipment SetEquipment::deserialize(::minecpp::network::message::Reader &reader) {
   SetEquipment result;
   result.entity_id = reader.read_uvarint();
   result.slot_id = reader.read_sbyte();
   const auto slot_has_value_0 = reader.read_byte();
   if (slot_has_value_0) {
      result.slot = play::Slot::deserialize(reader);
   }
   return result;
}

void SetHealth::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x57);
   writer.write_float(this->health);
   writer.write_varint(this->food);
   writer.write_float(this->food_saturation);
}

SetHealth SetHealth::deserialize(::minecpp::network::message::Reader &reader) {
   SetHealth result;
   result.health = reader.read_float();
   result.food = reader.read_varint();
   result.food_saturation = reader.read_float();
   return result;
}

void SystemChat::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x64);
   writer.write_string(this->message);
   writer.write_bool(this->is_actionbar);
}

SystemChat SystemChat::deserialize(::minecpp::network::message::Reader &reader) {
   SystemChat result;
   result.message = reader.read_string();
   result.is_actionbar = reader.read_bool();
   return result;
}

void PickupItem::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x67);
   writer.write_uvarint(this->collected_entity_id);
   writer.write_uvarint(this->collector_entity_id);
   writer.write_varint(this->count);
}

PickupItem PickupItem::deserialize(::minecpp::network::message::Reader &reader) {
   PickupItem result;
   result.collected_entity_id = reader.read_uvarint();
   result.collector_entity_id = reader.read_uvarint();
   result.count = reader.read_varint();
   return result;
}

void TeleportEntity::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x68);
   writer.write_uvarint(this->entity_id);
   this->position.serialize(writer);
   writer.write_byte(this->yaw);
   writer.write_byte(this->pitch);
   writer.write_bool(this->is_on_ground);
}

TeleportEntity TeleportEntity::deserialize(::minecpp::network::message::Reader &reader) {
   TeleportEntity result;
   result.entity_id = reader.read_uvarint();
   result.position = play::Vector3::deserialize(reader);
   result.yaw = reader.read_byte();
   result.pitch = reader.read_byte();
   result.is_on_ground = reader.read_bool();
   return result;
}

}