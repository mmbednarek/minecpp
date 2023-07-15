#pragma once
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::status::cb {

class Status {
 public:
   std::string status{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Status deserialize(::minecpp::network::message::Reader &reader);
};

class Ping {
 public:
   std::uint64_t payload{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Ping deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor, typename TClientInfo>
void visit_message(TVisitor &visitor, TClientInfo &client_info, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x00: {
      auto message = Status::deserialize(reader);
      visitor.on_status(client_info, message);
      break;
   }
   case 0x01: {
      auto message = Ping::deserialize(reader);
      visitor.on_ping(client_info, message);
      break;
   }
   default: 
      visitor.on_failure(client_info, message_id);
      break;
   }
}

}
