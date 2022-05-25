#ifndef MINECPP_STATE_H
#define MINECPP_STATE_H
#include <algorithm>
#include <string>
#include <variant>
#include <vector>

namespace minecpp::game {

struct BoolState
{};

struct IntState
{
   int min{}, max{};
};

struct EnumState
{
   std::vector<std::string> values{};
};

class State
{
   std::string m_name;
   std::variant<BoolState, IntState, EnumState> m_detail;

 public:
   explicit State(std::string_view name) :
       m_name(name),
       m_detail{std::in_place_type<BoolState>}
   {
   }

   State(std::string_view name, int min, int max) :
       m_name(name),
       m_detail{std::in_place_type<IntState>, min, max}
   {
   }

   State(std::string_view name, const std::vector<std::string> &enum_values) :
       m_name(name),
       m_detail{std::in_place_type<EnumState>, enum_values}
   {
   }

   [[nodiscard]] constexpr int value_count() const
   {
      return std::visit(
              [](auto &&detail) -> int {
                 using T = std::decay_t<decltype(detail)>;
                 if constexpr (std::is_same_v<T, BoolState>) {
                    return 2;
                 }
                 if constexpr (std::is_same_v<T, IntState>) {
                    return detail.max - detail.min + 1;
                 }
                 if constexpr (std::is_same_v<T, EnumState>) {
                    return detail.values.size();
                 }
                 return 0;
              },
              m_detail);
   }

   [[nodiscard]] std::string value_from_index(int index) const
   {
      return std::visit(
              [index](auto &&detail) -> std::string {
                 using T = std::decay_t<decltype(detail)>;
                 if constexpr (std::is_same_v<T, BoolState>) {
                    return index == 0 ? "true" : "false";
                 }
                 if constexpr (std::is_same_v<T, IntState>) {
                    return std::to_string(detail.min + index);
                 }
                 if constexpr (std::is_same_v<T, EnumState>) {
                    return detail.values[index];
                 }
                 return "";
              },
              m_detail);
   }

   [[nodiscard]] int index_from_value(std::string_view value) const
   {
      return std::visit(
              [value](auto &&detail) -> int {
                 using T = std::decay_t<decltype(detail)>;
                 if constexpr (std::is_same_v<T, BoolState>) {
                    return value == "true" ? 0 : 1;
                 }
                 if constexpr (std::is_same_v<T, IntState>) {
                    return std::atoi(value.data()) - detail.min;
                 }
                 if constexpr (std::is_same_v<T, EnumState>) {
                    return std::find(detail.values.begin(), detail.values.end(), value) -
                           detail.values.begin();
                 }
                 return 0;
              },
              m_detail);
   }

   [[nodiscard]] int index_from_value(int value) const
   {
      return std::visit(
              [value](auto &&detail) -> int {
                 using T = std::decay_t<decltype(detail)>;
                 if constexpr (std::is_same_v<T, BoolState>) {
                    return value == 0 ? 0 : 1;
                 }
                 if constexpr (std::is_same_v<T, IntState>) {
                    return value - detail.min;
                 }
                 if constexpr (std::is_same_v<T, EnumState>) {
                    auto it = std::find(detail.values.begin(), detail.values.end(), std::to_string(value));
                    if (it == detail.values.end())
                       return 0;
                    return it - detail.values.begin();
                 }
                 return 0;
              },
              m_detail);
   }

   [[nodiscard]] inline std::string_view name() const
   {
      return m_name;
   }
};
}// namespace minecpp::game

#endif//MINECPP_STATE_H
