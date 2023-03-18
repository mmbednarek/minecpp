#pragma once
#include "BaseVector.h"
#include "ProtoTypes.h"
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

   [[nodiscard]] static SelfType from_proto(const ProtoType &proto_vec)
   {
      return {proto_vec.x(), proto_vec.y(), proto_vec.z()};
   }

   [[nodiscard]] bool is_correct() const
   {
      return std::all_of(m_storage, m_storage + Count, [](const ValueType value) {
         return not std::isnan(value) and not std::isinf(value);
      });
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

template<>
struct fmt::formatter<minecpp::math::Vector3f>
{
   using Self = minecpp::math::Vector3f;

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
