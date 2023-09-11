#include "minecpp/network/NetworkUtil.h"
#include "net/storage/Serverbound.schema.h"
#include <algorithm>

namespace minecpp::net::storage::sb {

void SetClientId::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
   writer.write_big_endian(this->client_id);
}

SetClientId SetClientId::deserialize(::minecpp::network::message::Reader &reader) {
   SetClientId result;
   result.client_id = reader.read_big_endian<std::uint64_t>();
   return result;
}

void SubscribeChunk::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   network::write_vector2i(writer, this->position);
}

SubscribeChunk SubscribeChunk::deserialize(::minecpp::network::message::Reader &reader) {
   SubscribeChunk result;
   result.position = network::read_vector2i(reader);
   return result;
}

void StoreChunk::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x02);
   this->chunk.serialize(writer);
}

StoreChunk StoreChunk::deserialize(::minecpp::network::message::Reader &reader) {
   StoreChunk result;
   result.chunk = net::Chunk::deserialize(reader);
   return result;
}

void ChunkSubscription::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(static_cast<std::int32_t>(this->client_ids.size()));
   for (const auto &client_ids_value_0 : this->client_ids) {
      writer.write_big_endian(client_ids_value_0);
   }
}

ChunkSubscription ChunkSubscription::deserialize(::minecpp::network::message::Reader &reader) {
   ChunkSubscription result;
   auto client_ids_size_0 = reader.read_varint();
   result.client_ids.resize(static_cast<std::size_t>(client_ids_size_0));
   std::generate(result.client_ids.begin(), result.client_ids.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   return result;
}

}