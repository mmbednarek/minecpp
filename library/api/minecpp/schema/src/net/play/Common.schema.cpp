#include "net/play/Common.schema.h"
#include <algorithm>

namespace minecpp::net::play {

void Vector3::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_double(this->x);
   writer.write_double(this->y);
   writer.write_double(this->z);
}

Vector3 Vector3::deserialize(::minecpp::network::message::Reader &reader) {
   Vector3 result;
   result.x = reader.read_double();
   result.y = reader.read_double();
   result.z = reader.read_double();
   return result;
}

void Vector3f::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_float(this->x);
   writer.write_float(this->y);
   writer.write_float(this->z);
}

Vector3f Vector3f::deserialize(::minecpp::network::message::Reader &reader) {
   Vector3f result;
   result.x = reader.read_float();
   result.y = reader.read_float();
   result.z = reader.read_float();
   return result;
}

void Vector3s::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_big_endian(this->x);
   writer.write_big_endian(this->y);
   writer.write_big_endian(this->z);
}

Vector3s Vector3s::deserialize(::minecpp::network::message::Reader &reader) {
   Vector3s result;
   result.x = reader.read_big_endian<std::int16_t>();
   result.y = reader.read_big_endian<std::int16_t>();
   result.z = reader.read_big_endian<std::int16_t>();
   return result;
}

void Vector2i::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_big_endian(this->x);
   writer.write_big_endian(this->y);
}

Vector2i Vector2i::deserialize(::minecpp::network::message::Reader &reader) {
   Vector2i result;
   result.x = reader.read_big_endian<std::int32_t>();
   result.y = reader.read_big_endian<std::int32_t>();
   return result;
}

void Vector2vi::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(this->x);
   writer.write_varint(this->y);
}

Vector2vi Vector2vi::deserialize(::minecpp::network::message::Reader &reader) {
   Vector2vi result;
   result.x = reader.read_varint();
   result.y = reader.read_varint();
   return result;
}

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