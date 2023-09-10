#pragma once
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::engine::sb {

class AcceptPlayer {
 public:
   ::minecpp::util::Uuid player_id{};
   std::string name{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static AcceptPlayer deserialize(::minecpp::network::message::Reader &reader);
};

class RemovePlayer {
 public:
   ::minecpp::util::Uuid player_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static RemovePlayer deserialize(::minecpp::network::message::Reader &reader);
};

class PlayerMessage {
 public:
   ::minecpp::util::Uuid player_id{};
   std::vector<std::uint8_t> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PlayerMessage deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor, typename TClientInfo>
void visit_message(TVisitor &visitor, TClientInfo &client_info, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x00: {
      auto message = AcceptPlayer::deserialize(reader);
      visitor.on_accept_player(client_info, message);
      break;
   }
   case 0x01: {
      auto message = RemovePlayer::deserialize(reader);
      visitor.on_remove_player(client_info, message);
      break;
   }
   case 0x02: {
      auto message = PlayerMessage::deserialize(reader);
      visitor.on_player_message(client_info, message);
      break;
   }
   default: 
      visitor.on_failure(client_info, message_id);
      break;
   }
}

}
