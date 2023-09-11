#pragma once
#include "minecpp/net/Chunk.schema.h"
#include "minecpp/net/Common.schema.h"
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::storage::sb {

class SetClientId {
 public:
   std::uint64_t client_id{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SetClientId deserialize(::minecpp::network::message::Reader &reader);
};

class SubscribeChunk {
 public:
   ::minecpp::math::Vector2i position{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SubscribeChunk deserialize(::minecpp::network::message::Reader &reader);
};

class StoreChunk {
 public:
   net::Chunk chunk{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static StoreChunk deserialize(::minecpp::network::message::Reader &reader);
};

class ChunkSubscription {
 public:
   std::vector<std::uint64_t> client_ids{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ChunkSubscription deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor, typename TClientInfo>
void visit_message(TVisitor &visitor, TClientInfo &client_info, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x00: {
      auto message = SetClientId::deserialize(reader);
      visitor.on_set_client_id(client_info, message);
      break;
   }
   case 0x01: {
      auto message = SubscribeChunk::deserialize(reader);
      visitor.on_subscribe_chunk(client_info, message);
      break;
   }
   case 0x02: {
      auto message = StoreChunk::deserialize(reader);
      visitor.on_store_chunk(client_info, message);
      break;
   }
   default: 
      visitor.on_failure(client_info, message_id);
      break;
   }
}

}
