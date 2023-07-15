#pragma once
#include "./ExampleNbt.schema.h"
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::example1 {

class Item {
 public:
   std::string name{};
   std::int16_t count{};
   nbt::Properties props{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Item deserialize(::minecpp::network::message::Reader &reader);
};

class Person {
 public:
   std::string name{};
   std::string surname{};
   std::int32_t age{};
   std::vector<std::vector<Item>> inventory{};
   std::int32_t dimension_types{};
   ::minecpp::util::Uuid foo{};
   std::variant<float, std::int32_t, Item> opts{};
   std::map<std::uint8_t, std::string> more{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Person deserialize(::minecpp::network::message::Reader &reader);
};

class Car {
 public:
   std::string brand{};
   std::string vin{};
   std::int64_t mileage{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Car deserialize(::minecpp::network::message::Reader &reader);
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
   std::int8_t is_listed{};
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
   static PlayerInfoChange deserialize(::minecpp::network::message::Reader &reader, std::uint32_t action_bits);
};

class UpdatePlayerInfo {
 public:
   std::uint32_t action_bits{};
   std::vector<PlayerInfoChange> actions{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static UpdatePlayerInfo deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor>
void visit_message(TVisitor &visitor, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x01: {
      auto message = Person::deserialize(reader);
      visitor.on_person(message);
      break;
   }
   case 0x02: {
      auto message = Car::deserialize(reader);
      visitor.on_car(message);
      break;
   }
   case 36: {
      auto message = UpdatePlayerInfo::deserialize(reader);
      visitor.on_update_player_info(message);
      break;
   }
   default: 
      visitor.on_failure(message_id);
      break;
   }
}

}
