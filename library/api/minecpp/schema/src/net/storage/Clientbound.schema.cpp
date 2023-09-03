#include "minecpp/network/NetworkUtil.h"
#include "net/storage/Clientbound.schema.h"
#include <algorithm>

namespace minecpp::net::storage::cb {

void ReplyEmptyChunk::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x00);
   network::write_vector2i(writer, this->position);
}

ReplyEmptyChunk ReplyEmptyChunk::deserialize(::minecpp::network::message::Reader &reader) {
   ReplyEmptyChunk result;
   result.position = network::read_vector2i(reader);
   return result;
}

void ReplyChunk::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   this->chunk.serialize(writer);
}

ReplyChunk ReplyChunk::deserialize(::minecpp::network::message::Reader &reader) {
   ReplyChunk result;
   result.chunk = net::Chunk::deserialize(reader);
   return result;
}

}