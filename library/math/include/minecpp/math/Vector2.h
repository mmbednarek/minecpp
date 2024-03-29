#pragma once

#include "BaseVector.h"

#include <concepts>

namespace minecpp::math {

template<typename TValue>
   requires std::floating_point<TValue> || std::integral<TValue>
class BaseVector<TValue, 2>
{
 public:
   MCC_MATH_DEFINE_VECTOR_TRAITS(2)

   MCC_MATH_DEFINE_INDEX_GETTER_SETTER(x, 0)
   MCC_MATH_DEFINE_INDEX_GETTER_SETTER(y, 1)

   [[nodiscard]] static SelfType from_yaw(ValueType yaw)
   {
      return {std::cos(yaw), std::sin(yaw)};
   }
};

using Vector2  = BaseVector<double, 2>;
using Vector2f = BaseVector<float, 2>;
using Vector2i = BaseVector<int, 2>;

}// namespace minecpp::math
