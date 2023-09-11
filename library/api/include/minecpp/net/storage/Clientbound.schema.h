#pragma once
#include "minecpp/net/Chunk.schema.h"
#include "minecpp/net/Common.schema.h"
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::storage::cb {

class ReplyEmptyChunk {
 public:
   ::minecpp::math::Vector2i position{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ReplyEmptyChunk deserialize(::minecpp::network::message::Reader &reader);
};

class ReplyChunk {
 public:
   net::Chunk chunk{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ReplyChunk deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor, typename TClientInfo>
void visit_message(TVisitor &visitor, TClientInfo &client_info, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x00: {
      auto message = ReplyEmptyChunk::deserialize(reader);
      visitor.on_reply_empty_chunk(client_info, message);
      break;
   }
   case 0x01: {
      auto message = ReplyChunk::deserialize(reader);
      visitor.on_reply_chunk(client_info, message);
      break;
   }
   default: 
      visitor.on_failure(client_info, message_id);
      break;
   }
}

}
