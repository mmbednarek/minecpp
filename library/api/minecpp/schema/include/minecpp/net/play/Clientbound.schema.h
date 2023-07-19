#pragma once
#include "minecpp/nbt/block/Block.schema.h"
#include "minecpp/nbt/chunk/Chunk.schema.h"
#include "minecpp/nbt/repository/Codec.schema.h"
#include "minecpp/net/play/Common.schema.h"
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::play::cb {

class SpawnEntity {
 public:
   std::uint32_t entity_id{};
   ::minecpp::util::Uuid unique_id{};
   std::int32_t entity_type{};
   play::Vector3 position{};
   std::uint8_t pitch{};
   std::uint8_t yaw{};
   std::uint8_t head_yaw{};
   std::int32_t data{};
   play::Vector3s velocity{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SpawnEntity deserialize(::minecpp::network::message::Reader &reader);
};

class SpawnExperienceOrb {
 public:
   std::uint32_t entity_id{};
   play::Vector3 position{};
   std::int16_t xp_value{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SpawnExperienceOrb deserialize(::minecpp::network::message::Reader &reader);
};

class SpawnPlayer {
 public:
   std::uint32_t entity_id{};
   ::minecpp::util::Uuid player_id{};
   play::Vector3 position{};
   std::uint8_t yaw{};
   std::uint8_t pitch{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SpawnPlayer deserialize(::minecpp::network::message::Reader &reader);
};

class AnimateEntity {
 public:
   std::uint32_t entity_id{};
   std::uint8_t type{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static AnimateEntity deserialize(::minecpp::network::message::Reader &reader);
};

class AcknowledgeBlockChanges {
 public:
   std::uint32_t sequence_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static AcknowledgeBlockChanges deserialize(::minecpp::network::message::Reader &reader);
};

class BlockChange {
 public:
   std::uint64_t block_position{};
   std::int32_t block_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static BlockChange deserialize(::minecpp::network::message::Reader &reader);
};

class Difficulty {
 public:
   std::uint8_t difficulty{};
   std::int8_t locked{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Difficulty deserialize(::minecpp::network::message::Reader &reader);
};

class SetSlot {
 public:
   std::uint8_t window_id{};
   std::int32_t state_id{};
   std::int16_t slot_id{};
   std::optional<play::Slot> slot{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetSlot deserialize(::minecpp::network::message::Reader &reader);
};

class PluginMessage {
 public:
   std::string key{};
   std::string value{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PluginMessage deserialize(::minecpp::network::message::Reader &reader);
};

class Disconnect {
 public:
   std::string reason{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Disconnect deserialize(::minecpp::network::message::Reader &reader);
};

class EntityStatus {
 public:
   std::int32_t entity_id{};
   std::int8_t opcode{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static EntityStatus deserialize(::minecpp::network::message::Reader &reader);
};

class UnloadChunk {
 public:
   play::Vector2i position{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static UnloadChunk deserialize(::minecpp::network::message::Reader &reader);
};

class KeepAlive {
 public:
   std::int64_t time{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static KeepAlive deserialize(::minecpp::network::message::Reader &reader);
};

class BlockEntity {
 public:
   std::uint8_t position_xz{};
   std::int16_t y{};
   std::int32_t type{};
   nbt::block::BlockEntityData data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static BlockEntity deserialize(::minecpp::network::message::Reader &reader);
};

class LightData {
 public:
   bool trust_edges{};
   std::vector<std::uint64_t> sky_light_mask{};
   std::vector<std::uint64_t> block_light_mask{};
   std::vector<std::uint64_t> empty_sky_light_mask{};
   std::vector<std::uint64_t> empty_block_light_mask{};
   std::vector<std::vector<std::uint8_t>> sky_light{};
   std::vector<std::vector<std::uint8_t>> block_light{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static LightData deserialize(::minecpp::network::message::Reader &reader);
};

class UpdateChunk {
 public:
   play::Vector2i position{};
   nbt::chunk::HeightmapsNet heightmaps{};
   std::vector<std::uint8_t> data{};
   std::vector<BlockEntity> block_entities{};
   LightData light_data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static UpdateChunk deserialize(::minecpp::network::message::Reader &reader);
};

class UpdateLight {
 public:
   play::Vector2vi position{};
   LightData light_data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static UpdateLight deserialize(::minecpp::network::message::Reader &reader);
};

class DeathLocation {
 public:
   std::string dimension{};
   std::int64_t position{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static DeathLocation deserialize(::minecpp::network::message::Reader &reader);
};

class JoinGame {
 public:
   std::uint32_t entity_id{};
   bool is_hardcode{};
   std::int8_t game_mode{};
   std::int8_t previous_game_mode{};
   std::vector<std::string> available_dimensions{};
   nbt::repository::Registry dimension_codec{};
   std::string dimension_name{};
   std::string world_name{};
   std::uint64_t seed{};
   std::uint8_t max_players{};
   std::int32_t view_distance{};
   std::int32_t simulation_distance{};
   std::int8_t reduced_debug_info{};
   bool should_show_respawn_screen{};
   bool is_debug{};
   bool is_flat{};
   std::optional<DeathLocation> death_location{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static JoinGame deserialize(::minecpp::network::message::Reader &reader);
};

class EntityRelativeMove {
 public:
   std::uint32_t entity_id{};
   play::Vector3s difference{};
   bool is_on_ground{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static EntityRelativeMove deserialize(::minecpp::network::message::Reader &reader);
};

class EntityMove {
 public:
   std::uint32_t entity_id{};
   play::Vector3s difference{};
   std::uint8_t yaw{};
   std::uint8_t pitch{};
   bool is_on_ground{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static EntityMove deserialize(::minecpp::network::message::Reader &reader);
};

class EntityLook {
 public:
   std::uint32_t entity_id{};
   std::uint8_t yaw{};
   std::uint8_t pitch{};
   bool is_on_ground{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static EntityLook deserialize(::minecpp::network::message::Reader &reader);
};

class PlayerAbilities {
 public:
   std::uint8_t flags{};
   float fly_speed{};
   float field_of_view{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PlayerAbilities deserialize(::minecpp::network::message::Reader &reader);
};

class DisplayDeathScreen {
 public:
   std::uint32_t victim_entity_id{};
   std::uint32_t killer_entity_id{};
   std::string message{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static DisplayDeathScreen deserialize(::minecpp::network::message::Reader &reader);
};

class RemovePlayerInfo {
 public:
   std::vector<::minecpp::util::Uuid> player_ids{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static RemovePlayerInfo deserialize(::minecpp::network::message::Reader &reader);
};

class PlayerProperty {
 public:
   std::string key{};
   std::string value{};
   std::optional<std::string> signature{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PlayerProperty deserialize(::minecpp::network::message::Reader &reader);
};

class ActionAddPlayer {
 public:
   std::string name{};
   std::vector<PlayerProperty> properties{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ActionAddPlayer deserialize(::minecpp::network::message::Reader &reader);
};

class PlayerChatSignature {
 public:
   ::minecpp::util::Uuid chat_session_id{};
   std::uint64_t public_key_expiry{};
   std::string public_key{};
   std::string signature{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PlayerChatSignature deserialize(::minecpp::network::message::Reader &reader);
};

class ActionInitializeChat {
 public:
   std::optional<PlayerChatSignature> chat_signature{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ActionInitializeChat deserialize(::minecpp::network::message::Reader &reader);
};

class ActionSetGameMode {
 public:
   std::int32_t game_mode{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ActionSetGameMode deserialize(::minecpp::network::message::Reader &reader);
};

class ActionSetIsListed {
 public:
   bool is_listed{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ActionSetIsListed deserialize(::minecpp::network::message::Reader &reader);
};

class ActionSetLatency {
 public:
   std::int32_t ping{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ActionSetLatency deserialize(::minecpp::network::message::Reader &reader);
};

class ActionSetDisplayName {
 public:
   std::optional<std::string> display_name{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ActionSetDisplayName deserialize(::minecpp::network::message::Reader &reader);
};

class PlayerInfoChange {
 public:
   ::minecpp::util::Uuid player_id{};
   std::optional<ActionAddPlayer> add_player{};
   std::optional<ActionInitializeChat> initialize_chat{};
   std::optional<ActionSetGameMode> set_game_mode{};
   std::optional<ActionSetIsListed> set_is_listed{};
   std::optional<ActionSetLatency> set_latency{};
   std::optional<ActionSetDisplayName> set_display_name{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PlayerInfoChange deserialize(::minecpp::network::message::Reader &reader, std::uint8_t action_bits);
};

class UpdatePlayerInfo {
 public:
   std::uint8_t action_bits{};
   std::vector<PlayerInfoChange> actions{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static UpdatePlayerInfo deserialize(::minecpp::network::message::Reader &reader);
};

class PlayerPositionLook {
 public:
   play::Vector3 position{};
   float yaw{};
   float pitch{};
   std::uint8_t flags{};
   std::int32_t teleport_id{};
   bool has_dismounted_vehicle{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PlayerPositionLook deserialize(::minecpp::network::message::Reader &reader);
};

class RecipeGui {
 public:
   bool is_open{};
   bool is_filtering_craftable{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static RecipeGui deserialize(::minecpp::network::message::Reader &reader);
};

class RecipeList {
 public:
   std::vector<std::string> recipes{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static RecipeList deserialize(::minecpp::network::message::Reader &reader);
};

class RecipeBook {
 public:
   std::int32_t state{};
   RecipeGui crafting_table{};
   RecipeGui furnace{};
   RecipeGui blaster{};
   RecipeGui smoker{};
   std::vector<std::string> recipes{};
   std::optional<RecipeList> additional_recipes{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static RecipeBook deserialize(::minecpp::network::message::Reader &reader);
};

class RemoveEntities {
 public:
   std::vector<std::uint32_t> entity_ids{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static RemoveEntities deserialize(::minecpp::network::message::Reader &reader);
};

class Respawn {
 public:
   std::string dimension_codec{};
   std::string dimension_name{};
   std::uint64_t seed{};
   std::int8_t game_mode{};
   std::int8_t previous_game_mode{};
   bool is_debug{};
   bool is_flat{};
   std::uint8_t should_copy_metadata{};
   DeathLocation death_location{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Respawn deserialize(::minecpp::network::message::Reader &reader);
};

class EntityHeadLook {
 public:
   std::uint32_t entity_id{};
   std::uint8_t yaw{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static EntityHeadLook deserialize(::minecpp::network::message::Reader &reader);
};

class MultiBlockChange {
 public:
   std::uint64_t chunk_position{};
   bool should_distrust_edges{};
   std::vector<std::int64_t> block_changes{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static MultiBlockChange deserialize(::minecpp::network::message::Reader &reader);
};

class ChangeHeldItem {
 public:
   std::int8_t item_index{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ChangeHeldItem deserialize(::minecpp::network::message::Reader &reader);
};

class UpdateChunkPosition {
 public:
   play::Vector2vi chunk_position{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static UpdateChunkPosition deserialize(::minecpp::network::message::Reader &reader);
};

class SetDefaultSpawnPosition {
 public:
   std::uint64_t position{};
   float angle{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetDefaultSpawnPosition deserialize(::minecpp::network::message::Reader &reader);
};

class SetEntityMetadata {
 public:
   std::uint32_t entity_id{};
   std::map<std::uint8_t, std::variant<std::int8_t, std::int32_t, std::int64_t, float, std::string, play::Chat, std::optional<play::Chat>, std::optional<play::Slot>>> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetEntityMetadata deserialize(::minecpp::network::message::Reader &reader);
};

class SetEntityVelocity {
 public:
   std::uint32_t entity_id{};
   play::Vector3s velocity{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetEntityVelocity deserialize(::minecpp::network::message::Reader &reader);
};

class SetEquipment {
 public:
   std::uint32_t entity_id{};
   std::int8_t slot_id{};
   std::optional<play::Slot> slot{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetEquipment deserialize(::minecpp::network::message::Reader &reader);
};

class SetHealth {
 public:
   float health{};
   std::int32_t food{};
   float food_saturation{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetHealth deserialize(::minecpp::network::message::Reader &reader);
};

class SystemChat {
 public:
   std::string message{};
   std::int8_t type{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SystemChat deserialize(::minecpp::network::message::Reader &reader);
};

class PickupItem {
 public:
   std::uint32_t collected_entity_id{};
   std::uint32_t collector_entity_id{};
   std::int32_t count{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PickupItem deserialize(::minecpp::network::message::Reader &reader);
};

class TeleportEntity {
 public:
   std::uint32_t entity_id{};
   play::Vector3 position{};
   std::uint8_t yaw{};
   std::uint8_t pitch{};
   bool is_on_ground{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static TeleportEntity deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor, typename TClientInfo>
void visit_message(TVisitor &visitor, TClientInfo &client_info, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x00: {
      auto message = SpawnEntity::deserialize(reader);
      visitor.on_spawn_entity(client_info, message);
      break;
   }
   case 0x01: {
      auto message = SpawnExperienceOrb::deserialize(reader);
      visitor.on_spawn_experience_orb(client_info, message);
      break;
   }
   case 0x02: {
      auto message = SpawnPlayer::deserialize(reader);
      visitor.on_spawn_player(client_info, message);
      break;
   }
   case 0x03: {
      auto message = AnimateEntity::deserialize(reader);
      visitor.on_animate_entity(client_info, message);
      break;
   }
   case 0x05: {
      auto message = AcknowledgeBlockChanges::deserialize(reader);
      visitor.on_acknowledge_block_changes(client_info, message);
      break;
   }
   case 0x09: {
      auto message = BlockChange::deserialize(reader);
      visitor.on_block_change(client_info, message);
      break;
   }
   case 0x0B: {
      auto message = Difficulty::deserialize(reader);
      visitor.on_difficulty(client_info, message);
      break;
   }
   case 0x12: {
      auto message = SetSlot::deserialize(reader);
      visitor.on_set_slot(client_info, message);
      break;
   }
   case 0x15: {
      auto message = PluginMessage::deserialize(reader);
      visitor.on_plugin_message(client_info, message);
      break;
   }
   case 0x17: {
      auto message = Disconnect::deserialize(reader);
      visitor.on_disconnect(client_info, message);
      break;
   }
   case 0x19: {
      auto message = EntityStatus::deserialize(reader);
      visitor.on_entity_status(client_info, message);
      break;
   }
   case 0x1B: {
      auto message = UnloadChunk::deserialize(reader);
      visitor.on_unload_chunk(client_info, message);
      break;
   }
   case 0x1F: {
      auto message = KeepAlive::deserialize(reader);
      visitor.on_keep_alive(client_info, message);
      break;
   }
   case 0x20: {
      auto message = UpdateChunk::deserialize(reader);
      visitor.on_update_chunk(client_info, message);
      break;
   }
   case 0x23: {
      auto message = UpdateLight::deserialize(reader);
      visitor.on_update_light(client_info, message);
      break;
   }
   case 0x24: {
      auto message = JoinGame::deserialize(reader);
      visitor.on_join_game(client_info, message);
      break;
   }
   case 0x27: {
      auto message = EntityRelativeMove::deserialize(reader);
      visitor.on_entity_relative_move(client_info, message);
      break;
   }
   case 0x28: {
      auto message = EntityMove::deserialize(reader);
      visitor.on_entity_move(client_info, message);
      break;
   }
   case 0x29: {
      auto message = EntityLook::deserialize(reader);
      visitor.on_entity_look(client_info, message);
      break;
   }
   case 0x30: {
      auto message = PlayerAbilities::deserialize(reader);
      visitor.on_player_abilities(client_info, message);
      break;
   }
   case 0x34: {
      auto message = DisplayDeathScreen::deserialize(reader);
      visitor.on_display_death_screen(client_info, message);
      break;
   }
   case 0x35: {
      auto message = RemovePlayerInfo::deserialize(reader);
      visitor.on_remove_player_info(client_info, message);
      break;
   }
   case 0x36: {
      auto message = UpdatePlayerInfo::deserialize(reader);
      visitor.on_update_player_info(client_info, message);
      break;
   }
   case 0x38: {
      auto message = PlayerPositionLook::deserialize(reader);
      visitor.on_player_position_look(client_info, message);
      break;
   }
   case 0x39: {
      auto message = RecipeBook::deserialize(reader);
      visitor.on_recipe_book(client_info, message);
      break;
   }
   case 0x3A: {
      auto message = RemoveEntities::deserialize(reader);
      visitor.on_remove_entities(client_info, message);
      break;
   }
   case 0x3D: {
      auto message = Respawn::deserialize(reader);
      visitor.on_respawn(client_info, message);
      break;
   }
   case 0x3E: {
      auto message = EntityHeadLook::deserialize(reader);
      visitor.on_entity_head_look(client_info, message);
      break;
   }
   case 0x3F: {
      auto message = MultiBlockChange::deserialize(reader);
      visitor.on_multi_block_change(client_info, message);
      break;
   }
   case 0x49: {
      auto message = ChangeHeldItem::deserialize(reader);
      visitor.on_change_held_item(client_info, message);
      break;
   }
   case 0x4A: {
      auto message = UpdateChunkPosition::deserialize(reader);
      visitor.on_update_chunk_position(client_info, message);
      break;
   }
   case 0x4C: {
      auto message = SetDefaultSpawnPosition::deserialize(reader);
      visitor.on_set_default_spawn_position(client_info, message);
      break;
   }
   case 0x4E: {
      auto message = SetEntityMetadata::deserialize(reader);
      visitor.on_set_entity_metadata(client_info, message);
      break;
   }
   case 0x50: {
      auto message = SetEntityVelocity::deserialize(reader);
      visitor.on_set_entity_velocity(client_info, message);
      break;
   }
   case 0x51: {
      auto message = SetEquipment::deserialize(reader);
      visitor.on_set_equipment(client_info, message);
      break;
   }
   case 0x53: {
      auto message = SetHealth::deserialize(reader);
      visitor.on_set_health(client_info, message);
      break;
   }
   case 0x60: {
      auto message = SystemChat::deserialize(reader);
      visitor.on_system_chat(client_info, message);
      break;
   }
   case 0x63: {
      auto message = PickupItem::deserialize(reader);
      visitor.on_pickup_item(client_info, message);
      break;
   }
   case 0x64: {
      auto message = TeleportEntity::deserialize(reader);
      visitor.on_teleport_entity(client_info, message);
      break;
   }
   default: 
      visitor.on_failure(client_info, message_id);
      break;
   }
}

}
