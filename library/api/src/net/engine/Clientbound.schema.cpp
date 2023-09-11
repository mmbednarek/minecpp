#include "minecpp/network/NetworkUtil.h"
#include "net/engine/Clientbound.schema.h"
#include <algorithm>

namespace minecpp::net::engine::cb {

void SendMsgToSinglePlayer::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
   writer.write_uuid(this->player_id);
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &data_value_0 : this->data) {
      writer.write_byte(data_value_0);
   }
}

SendMsgToSinglePlayer SendMsgToSinglePlayer::deserialize(::minecpp::network::message::Reader &reader) {
   SendMsgToSinglePlayer result;
   result.player_id = reader.read_uuid();
   auto data_size_0 = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size_0));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      return reader.read_byte();
   });
   return result;
}

void SendMsgToSomePlayers::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   writer.write_varint(static_cast<std::int32_t>(this->player_ids.size()));
   for (const auto &player_ids_value_0 : this->player_ids) {
      writer.write_uuid(player_ids_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &data_value_0 : this->data) {
      writer.write_byte(data_value_0);
   }
}

SendMsgToSomePlayers SendMsgToSomePlayers::deserialize(::minecpp::network::message::Reader &reader) {
   SendMsgToSomePlayers result;
   auto player_ids_size_0 = reader.read_varint();
   result.player_ids.resize(static_cast<std::size_t>(player_ids_size_0));
   std::generate(result.player_ids.begin(), result.player_ids.end(), [&reader]() {
      return reader.read_uuid();
   });
   auto data_size_0 = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size_0));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      return reader.read_byte();
   });
   return result;
}

void SendMsgToAllPlayers::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x02);
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &data_value_0 : this->data) {
      writer.write_byte(data_value_0);
   }
}

SendMsgToAllPlayers SendMsgToAllPlayers::deserialize(::minecpp::network::message::Reader &reader) {
   SendMsgToAllPlayers result;
   auto data_size_0 = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size_0));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      return reader.read_byte();
   });
   return result;
}

void SendMsgToAllPlayersExcept::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x03);
   writer.write_uuid(this->player_id);
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &data_value_0 : this->data) {
      writer.write_byte(data_value_0);
   }
}

SendMsgToAllPlayersExcept SendMsgToAllPlayersExcept::deserialize(::minecpp::network::message::Reader &reader) {
   SendMsgToAllPlayersExcept result;
   result.player_id = reader.read_uuid();
   auto data_size_0 = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size_0));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      return reader.read_byte();
   });
   return result;
}

}