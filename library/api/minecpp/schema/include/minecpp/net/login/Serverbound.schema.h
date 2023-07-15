#pragma once
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::login::sb {

class LoginStart {
 public:
   std::string name{};
   std::optional<::minecpp::util::Uuid> player_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static LoginStart deserialize(::minecpp::network::message::Reader &reader);
};

class EncryptionResponse {
 public:
   std::vector<std::uint8_t> shared_secret{};
   std::vector<std::uint8_t> token{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static EncryptionResponse deserialize(::minecpp::network::message::Reader &reader);
};

class PluginResponse {
 public:
   std::int32_t message_id{};
   std::int8_t is_successful{};
   std::vector<std::uint8_t> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PluginResponse deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor, typename TClientInfo>
void visit_message(TVisitor &visitor, TClientInfo &client_info, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x00: {
      auto message = LoginStart::deserialize(reader);
      visitor.on_login_start(client_info, message);
      break;
   }
   case 0x01: {
      auto message = EncryptionResponse::deserialize(reader);
      visitor.on_encryption_response(client_info, message);
      break;
   }
   case 0x02: {
      auto message = PluginResponse::deserialize(reader);
      visitor.on_plugin_response(client_info, message);
      break;
   }
   default: 
      visitor.on_failure(client_info, message_id);
      break;
   }
}

}
