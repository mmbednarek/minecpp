#pragma once

#include "message/Reader.h"
#include "message/Writer.h"
#include "minecpp/math/Vector2.h"
#include "minecpp/math/Vector3.h"

namespace minecpp::network {

void write_vector3(message::Writer &writer, const math::Vector3 &value);
math::Vector3 read_vector3(message::Reader &reader);
void write_vector3f(message::Writer &writer, const math::Vector3f &value);
math::Vector3f read_vector3f(message::Reader &reader);
void write_vector3s(message::Writer &writer, const math::Vector3s &value);
math::Vector3s read_vector3s(message::Reader &reader);
void write_vector2i(message::Writer &writer, const math::Vector2i &value);
math::Vector2i read_vector2i(message::Reader &reader);
void write_vector2vi(message::Writer &writer, const math::Vector2i &value);
math::Vector2i read_vector2vi(message::Reader &reader);

void write_angle(message::Writer &writer, float value);
float read_angle(message::Reader &reader);

}// namespace minecpp::network