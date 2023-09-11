#pragma once
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::login::cb {

class Disconnect {
 public:
   std::string reason{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Disconnect deserialize(::minecpp::network::message::Reader &reader);
};

class EncryptionRequest {
 public:
   std::string server_id{};
   std::vector<std::uint8_t> public_key{};
   std::vector<std::uint8_t> token{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static EncryptionRequest deserialize(::minecpp::network::message::Reader &reader);
};

class LoginProperty {
 public:
   std::string key{};
   std::string value{};
   std::optional<std::string> signature{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static LoginProperty deserialize(::minecpp::network::message::Reader &reader);
};

class LoginSuccess {
 public:
   ::minecpp::util::Uuid player_id{};
   std::string username{};
   std::vector<LoginProperty> properties{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static LoginSuccess deserialize(::minecpp::network::message::Reader &reader);
};

class SetCompression {
 public:
   std::int32_t threshold{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetCompression deserialize(::minecpp::network::message::Reader &reader);
};

class PluginRequest {
 public:
   std::int32_t message_id{};
   std::string channel{};
   std::vector<std::uint8_t> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PluginRequest deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor, typename TClientInfo>
void visit_message(TVisitor &visitor, TClientInfo &client_info, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x00: {
      auto message = Disconnect::deserialize(reader);
      visitor.on_disconnect(client_info, message);
      break;
   }
   case 0x01: {
      auto message = EncryptionRequest::deserialize(reader);
      visitor.on_encryption_request(client_info, message);
      break;
   }
   case 0x02: {
      auto message = LoginSuccess::deserialize(reader);
      visitor.on_login_success(client_info, message);
      break;
   }
   case 0x03: {
      auto message = SetCompression::deserialize(reader);
      visitor.on_set_compression(client_info, message);
      break;
   }
   case 0x04: {
      auto message = PluginRequest::deserialize(reader);
      visitor.on_plugin_request(client_info, message);
      break;
   }
   default: 
      visitor.on_failure(client_info, message_id);
      break;
   }
}

}
