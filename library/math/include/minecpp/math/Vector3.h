#pragma once
#include "BaseVector.h"

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
};

using Vector3  = BaseVector<double, 3>;
using Vector3f = BaseVector<float, 3>;
using Vector3i = BaseVector<int, 3>;

}// namespace minecpp::math
