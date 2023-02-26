#pragma once
#include "BaseVector.h"
#include "ProtoTypes.h"
#include "Rotation.h"
#include <fmt/format.h>

namespace minecpp::math {

template<typename TValue>
   requires std::floating_point<TValue> || std::integral<TValue>
class BaseVector<TValue, 3>
{
 public:
   MCC_MATH_DEFINE_VECTOR_TRAITS(3)

   MCC_MATH_DEFINE_INDEX_GETTER_SETTER(x, 0)
   MCC_MATH_DEFINE_INDEX_GETTER_SETTER(y, 1)
   MCC_MATH_DEFINE_INDEX_GETTER_SETTER(z, 2)

   BaseVector<TValue, 2> flat() const
   {
      return {x(), z()};
   }

   TValue length() const
   {
      return std::sqrt(this->transform([](TValue value) { return value * value; }).sum());
   }

   BaseVector<TValue, 3> normalize() const
   {
      return this->transform([l = this->length()](TValue value) { return value / l; });
   }

   [[nodiscard]] static SelfType from_proto(const ProtoType &proto_vec)
   {
      return {proto_vec.x(), proto_vec.y(), proto_vec.z()};
   }

   [[nodiscard]] static SelfType from_yaw_and_pitch(Radians yaw, Radians pitch)
   {
      return {static_cast<ValueType>(std::cos(yaw)), static_cast<ValueType>(std::sin(pitch)),
              static_cast<ValueType>(std::sin(yaw))};
   }

   [[nodiscard]] ProtoType to_proto() const
   {
      ProtoType result;
      result.set_x(this->x());
      result.set_y(this->y());
      result.set_z(this->z());
      return result;
   }
};

using Vector3  = BaseVector<double, 3>;
using Vector3f = BaseVector<float, 3>;
using Vector3s = BaseVector<short, 3>;
using Vector3i = BaseVector<int, 3>;
using Vector3l = BaseVector<std::int64_t, 3>;

}// namespace minecpp::math

template<>
struct fmt::formatter<minecpp::math::Vector3>
{
   using Self = minecpp::math::Vector3;

   template<typename ParseContext>
   constexpr auto parse(ParseContext &ctx)
   {
      return ctx.begin();
   }

   template<typename FormatContext>
   auto format(const Self &s, FormatContext &ctx)
   {
      return format_to(ctx.out(), "{}, {}, {}", s.x(), s.y(), s.z());
   }
};
