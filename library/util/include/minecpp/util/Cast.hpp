#pragma once

#include <utility>

namespace minecpp::util {

template<typename TTargetType, typename TSourceType>
TTargetType unsafe_cast(TSourceType&& value) {
   using SourceType = std::decay_t<TSourceType>;

   union {
      SourceType source;
      TTargetType target;
   };

   static_assert(sizeof(TTargetType) == sizeof(SourceType), "invalid size");

   source = std::forward<TSourceType>(value);
   return target;
}

}