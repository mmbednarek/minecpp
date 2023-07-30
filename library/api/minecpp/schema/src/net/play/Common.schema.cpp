#include "minecpp/network/NetworkUtil.h"
#include "net/play/Common.schema.h"
#include <algorithm>

namespace minecpp::net::play {

void Chat::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->format);
}

Chat Chat::deserialize(::minecpp::network::message::Reader &reader) {
   Chat result;
   result.format = reader.read_string();
   return result;
}

void Slot::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(this->item_id);
   writer.write_sbyte(this->item_count);
   this->data.serialize(writer.raw_stream(), "");
}

Slot Slot::deserialize(::minecpp::network::message::Reader &reader) {
   Slot result;
   result.item_id = reader.read_varint();
   result.item_count = reader.read_sbyte();
   result.data = nbt::item::SlotData::deserialize(reader.raw_stream());
   return result;
}

}