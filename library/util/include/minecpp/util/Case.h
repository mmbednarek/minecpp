#pragma once
#include <cctype>

namespace minecpp::util {

template<typename TInIterator, typename TOutIterator>
void convert_to_snake_case(TInIterator beg, TInIterator end, TOutIterator out)
{
   bool previous_lower = false;

   for (auto at = beg; at != end; ++at) {
      if (std::isupper(*at)) {
         if (previous_lower) {
            *out = '_';
            ++out;
         }
         *out = static_cast<char>(std::tolower(*at));
         ++out;
         previous_lower = false;
         continue;
      }
      *out = *at;
      ++out;
      previous_lower = true;
   }
}

}// namespace minecpp::util