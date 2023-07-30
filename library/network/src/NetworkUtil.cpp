#include "NetworkUtil.h"

namespace minecpp::network {

void write_vector3(message::Writer &writer, const math::Vector3 &value)
{
   writer.write_double(value.x());
   writer.write_double(value.y());
   writer.write_double(value.z());
}

math::Vector3 read_vector3(message::Reader &reader)
{
   math::Vector3 result{reader.read_double(), reader.read_double(), reader.read_double()};
   return result;
}

void write_vector3f(message::Writer &writer, const math::Vector3f &value)
{
   writer.write_float(value.x());
   writer.write_float(value.y());
   writer.write_float(value.z());
}

math::Vector3f read_vector3f(message::Reader &reader)
{
   math::Vector3f result{reader.read_float(), reader.read_float(), reader.read_float()};
   return result;
}

void write_vector3s(message::Writer &writer, const math::Vector3s &value)
{
   writer.write_big_endian(value.x());
   writer.write_big_endian(value.y());
   writer.write_big_endian(value.z());
}

math::Vector3s read_vector3s(message::Reader &reader)
{
   return minecpp::math::Vector3s{reader.read_big_endian<short>(), reader.read_big_endian<short>(),
                                  reader.read_big_endian<short>()};
}

void write_vector2i(message::Writer &writer, const math::Vector2i &value)
{
   writer.write_big_endian(value.x());
   writer.write_big_endian(value.y());
}

math::Vector2i read_vector2i(message::Reader &reader)
{
   return minecpp::math::Vector2i{reader.read_big_endian<int>(), reader.read_big_endian<int>()};
}

void write_vector2vi(message::Writer &writer, const math::Vector2i &value)
{
   writer.write_varint(value.x());
   writer.write_varint(value.y());
}

math::Vector2i read_vector2vi(message::Reader &reader)
{
   return minecpp::math::Vector2i{reader.read_varint(), reader.read_varint()};
}

void write_angle(message::Writer &writer, float value)
{
   writer.write_byte(static_cast<std::uint8_t>(value / 360.0f * 256.0f));
}

float read_angle(message::Reader &reader)
{
   return static_cast<float>(reader.read_byte()) * 360.0f / 256.0f;
}

}// namespace minecpp::network
