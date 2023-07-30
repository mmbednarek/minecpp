#pragma once
#include "minecpp/net/play/Common.schema.h"
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::play::sb {

class ConfirmTeleport {
 public:
   std::int32_t teleport_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ConfirmTeleport deserialize(::minecpp::network::message::Reader &reader);
};

class ChatCommand {
 public:
   std::string command{};
   std::uint64_t timestamp{};
   std::uint64_t salt{};
   std::map<std::string, std::string> argument_signatures{};
   std::int32_t message_count{};
   std::vector<std::uint64_t> acknowledged{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ChatCommand deserialize(::minecpp::network::message::Reader &reader);
};

class ChatMessage {
 public:
   std::string message{};
   std::uint64_t timestamp{};
   std::uint64_t salt{};
   std::optional<std::string> signature{};
   std::int32_t message_count{};
   std::vector<std::uint64_t> acknowledged{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ChatMessage deserialize(::minecpp::network::message::Reader &reader);
};

class ClientCommand {
 public:
   std::int32_t action_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ClientCommand deserialize(::minecpp::network::message::Reader &reader);
};

class ClientSettings {
 public:
   std::string locale{};
   std::uint8_t view_distance{};
   std::int32_t chat_mode{};
   bool are_colors_enabled{};
   std::uint8_t displayed_skin_parts{};
   std::int8_t main_hand{};
   bool is_text_filtering_enabled{};
   bool are_players_listed{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ClientSettings deserialize(::minecpp::network::message::Reader &reader);
};

class ClickWindow {
 public:
   std::uint8_t window_id{};
   std::int32_t state_id{};
   std::int16_t clicked_slot{};
   std::uint8_t button{};
   std::int32_t mode{};
   std::map<std::uint16_t, std::optional<play::Slot>> slots{};
   std::optional<play::Slot> carried_item{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ClickWindow deserialize(::minecpp::network::message::Reader &reader);
};

class CloseWindow {
 public:
   std::uint8_t window_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static CloseWindow deserialize(::minecpp::network::message::Reader &reader);
};

class PluginMessage {
 public:
   std::string channel{};
   std::string data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PluginMessage deserialize(::minecpp::network::message::Reader &reader);
};

class InteractTarget {
 public:
   ::minecpp::math::Vector3f position{};
   std::int32_t hand{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static InteractTarget deserialize(::minecpp::network::message::Reader &reader);
};

class Interact {
 public:
   std::uint32_t entity_id{};
   std::int32_t type{};
   std::optional<InteractTarget> target{};
   bool is_sneaking{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Interact deserialize(::minecpp::network::message::Reader &reader);
};

class KeepAlive {
 public:
   std::uint64_t time{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static KeepAlive deserialize(::minecpp::network::message::Reader &reader);
};

class SetPlayerPosition {
 public:
   ::minecpp::math::Vector3 position{};
   bool is_on_ground{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetPlayerPosition deserialize(::minecpp::network::message::Reader &reader);
};

class SetPlayerPositionAndRotation {
 public:
   ::minecpp::math::Vector3 position{};
   float yaw{};
   float pitch{};
   bool is_on_ground{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetPlayerPositionAndRotation deserialize(::minecpp::network::message::Reader &reader);
};

class SetPlayerRotation {
 public:
   float yaw{};
   float pitch{};
   bool is_on_ground{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetPlayerRotation deserialize(::minecpp::network::message::Reader &reader);
};

class SetIsPlayerOnGround {
 public:
   bool is_on_ground{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetIsPlayerOnGround deserialize(::minecpp::network::message::Reader &reader);
};

class PlayerDigging {
 public:
   std::int32_t state{};
   std::uint64_t position{};
   std::int8_t facing{};
   std::int32_t sequence_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PlayerDigging deserialize(::minecpp::network::message::Reader &reader);
};

class PlayerCommand {
 public:
   std::int32_t entity_id{};
   std::int32_t action_id{};
   std::int32_t jump_boost{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PlayerCommand deserialize(::minecpp::network::message::Reader &reader);
};

class SetHeldItem {
 public:
   std::uint16_t slot_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetHeldItem deserialize(::minecpp::network::message::Reader &reader);
};

class AnimateHand {
 public:
   std::int32_t hand{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static AnimateHand deserialize(::minecpp::network::message::Reader &reader);
};

class UseItemOn {
 public:
   std::int32_t hand{};
   std::uint64_t position{};
   std::int32_t facing{};
   ::minecpp::math::Vector3f cursor_position{};
   bool is_inside_block{};
   std::int32_t sequence_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static UseItemOn deserialize(::minecpp::network::message::Reader &reader);
};

class UseItem {
 public:
   std::int32_t hand{};
   std::int32_t sequence_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static UseItem deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor, typename TClientInfo>
void visit_message(TVisitor &visitor, TClientInfo &client_info, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x00: {
      auto message = ConfirmTeleport::deserialize(reader);
      visitor.on_confirm_teleport(client_info, message);
      break;
   }
   case 0x04: {
      auto message = ChatCommand::deserialize(reader);
      visitor.on_chat_command(client_info, message);
      break;
   }
   case 0x05: {
      auto message = ChatMessage::deserialize(reader);
      visitor.on_chat_message(client_info, message);
      break;
   }
   case 0x07: {
      auto message = ClientCommand::deserialize(reader);
      visitor.on_client_command(client_info, message);
      break;
   }
   case 0x08: {
      auto message = ClientSettings::deserialize(reader);
      visitor.on_client_settings(client_info, message);
      break;
   }
   case 0x0B: {
      auto message = ClickWindow::deserialize(reader);
      visitor.on_click_window(client_info, message);
      break;
   }
   case 0x0C: {
      auto message = CloseWindow::deserialize(reader);
      visitor.on_close_window(client_info, message);
      break;
   }
   case 0x0D: {
      auto message = PluginMessage::deserialize(reader);
      visitor.on_plugin_message(client_info, message);
      break;
   }
   case 0x10: {
      auto message = Interact::deserialize(reader);
      visitor.on_interact(client_info, message);
      break;
   }
   case 0x12: {
      auto message = KeepAlive::deserialize(reader);
      visitor.on_keep_alive(client_info, message);
      break;
   }
   case 0x14: {
      auto message = SetPlayerPosition::deserialize(reader);
      visitor.on_set_player_position(client_info, message);
      break;
   }
   case 0x15: {
      auto message = SetPlayerPositionAndRotation::deserialize(reader);
      visitor.on_set_player_position_and_rotation(client_info, message);
      break;
   }
   case 0x16: {
      auto message = SetPlayerRotation::deserialize(reader);
      visitor.on_set_player_rotation(client_info, message);
      break;
   }
   case 0x17: {
      auto message = SetIsPlayerOnGround::deserialize(reader);
      visitor.on_set_is_player_on_ground(client_info, message);
      break;
   }
   case 0x1D: {
      auto message = PlayerDigging::deserialize(reader);
      visitor.on_player_digging(client_info, message);
      break;
   }
   case 0x1E: {
      auto message = PlayerCommand::deserialize(reader);
      visitor.on_player_command(client_info, message);
      break;
   }
   case 0x28: {
      auto message = SetHeldItem::deserialize(reader);
      visitor.on_set_held_item(client_info, message);
      break;
   }
   case 0x2F: {
      auto message = AnimateHand::deserialize(reader);
      visitor.on_animate_hand(client_info, message);
      break;
   }
   case 0x31: {
      auto message = UseItemOn::deserialize(reader);
      visitor.on_use_item_on(client_info, message);
      break;
   }
   case 0x32: {
      auto message = UseItem::deserialize(reader);
      visitor.on_use_item(client_info, message);
      break;
   }
   default: 
      visitor.on_failure(client_info, message_id);
      break;
   }
}

}
