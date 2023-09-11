#pragma once
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::engine::cb {

class SendMsgToSinglePlayer {
 public:
   ::minecpp::util::Uuid player_id{};
   std::vector<std::uint8_t> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SendMsgToSinglePlayer deserialize(::minecpp::network::message::Reader &reader);
};

class SendMsgToSomePlayers {
 public:
   std::vector<::minecpp::util::Uuid> player_ids{};
   std::vector<std::uint8_t> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SendMsgToSomePlayers deserialize(::minecpp::network::message::Reader &reader);
};

class SendMsgToAllPlayers {
 public:
   std::vector<std::uint8_t> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SendMsgToAllPlayers deserialize(::minecpp::network::message::Reader &reader);
};

class SendMsgToAllPlayersExcept {
 public:
   ::minecpp::util::Uuid player_id{};
   std::vector<std::uint8_t> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SendMsgToAllPlayersExcept deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor, typename TClientInfo>
void visit_message(TVisitor &visitor, TClientInfo &client_info, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x00: {
      auto message = SendMsgToSinglePlayer::deserialize(reader);
      visitor.on_send_msg_to_single_player(client_info, message);
      break;
   }
   case 0x01: {
      auto message = SendMsgToSomePlayers::deserialize(reader);
      visitor.on_send_msg_to_some_players(client_info, message);
      break;
   }
   case 0x02: {
      auto message = SendMsgToAllPlayers::deserialize(reader);
      visitor.on_send_msg_to_all_players(client_info, message);
      break;
   }
   case 0x03: {
      auto message = SendMsgToAllPlayersExcept::deserialize(reader);
      visitor.on_send_msg_to_all_players_except(client_info, message);
      break;
   }
   default: 
      visitor.on_failure(client_info, message_id);
      break;
   }
}

}
