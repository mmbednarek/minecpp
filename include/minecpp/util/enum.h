#pragma once
#include <algorithm>
#include <array>
#include <stdexcept>
#include <string>
#include <utility>

template<char... chars>
using enum_string = std::integer_sequence<char, chars...>;

template<typename C, C... chars>
constexpr enum_string<chars...> operator"" _enumerator()
{
   return {};
}

#define ENU(value) decltype(value##_enumerator)

template<typename T>
concept Enumerable = requires(T a, size_t s, std::string_view str, uint32_t index)
{
   s     = T::num();
   str   = a.str();
   index = a.index();
};

namespace minecpp::util {

template<typename>
struct string_conv_helper;

template<char... chars>
struct string_conv_helper<enum_string<chars...>>
{
   std::string value{chars...};
};

template<size_t Total, typename First, typename... Rest>
void put_strings(std::array<std::string, Total> &arr, size_t index)
{
   arr[index] = string_conv_helper<First>{}.value;
   if constexpr (sizeof...(Rest) > 0) {
      put_strings<Total, Rest...>(arr, index + 1);
   }
}

template<typename... Enums>
std::array<std::string, sizeof...(Enums)> make_enum_array()
{
   std::array<std::string, sizeof...(Enums)> result;
   put_strings<sizeof...(Enums), Enums...>(result, 0);
   return result;
}

template<typename Cmp, typename First, typename... Rest>
constexpr uint32_t find_enum(uint32_t index)
{
   if constexpr (std::is_same<Cmp, First>()) {
      return index;
   } else {
      static_assert(sizeof...(Rest) > 0);
      return find_enum<Cmp, Rest...>(index + 1);
   }
}

template<typename... Enums>
class Enum
{
   static const std::array<std::string, sizeof...(Enums)> strings;
   uint32_t i;

 public:
   Enum() :
       i(0)
   {
   }

   explicit constexpr Enum(uint32_t index) :
       i(index)
   {
      if (index >= sizeof...(Enums)) {
         throw std::runtime_error("invalid enum index");
      }
   }

   explicit Enum(const char *name) :
       i(std::distance(strings.begin(), std::find(strings.begin(), strings.end(), name)))
   {
      if (i >= sizeof...(Enums)) {
         throw std::runtime_error("invalid enum index");
      }
   }

   template<typename Cmp>
   static constexpr Enum<Enums...> from()
   {
      return Enum<Enums...>(find_enum<Cmp, Enums...>(0));
   }

   template<typename Cmp>
   static constexpr uint32_t index_of()
   {
      return find_enum<Cmp, Enums...>(0);
   }

   static constexpr size_t num() { return sizeof...(Enums); }

   [[nodiscard]] constexpr std::string_view str() const { return strings[i]; }

   [[nodiscard]] constexpr uint32_t index() const { return i; }
};

template<typename... Enums>
const std::array<std::string, sizeof...(Enums)> Enum<Enums...>::strings = make_enum_array<Enums...>();

}// namespace minecpp::util