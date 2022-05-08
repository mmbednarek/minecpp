#pragma once
#include "string.h"
#include <cstdint>
#include <fmt/core.h>
#include <ostream>

namespace minecpp::util {

constexpr static void apply_indent(std::ostream &os, std::uint32_t ident_level) {
   for (std::uint32_t i = 0; i < ident_level; ++i)
      os << "   ";
}

class ScriptWriter {
   std::ostream &os;
   std::uint32_t ident_level = 0;

 public:
   explicit ScriptWriter(std::ostream &os);

   void ident();
   void deindent();

   void line(std::string_view sv);

   template<typename... Args>
   void line(fmt::format_string<Args...> sv, Args... args) {
      apply_indent(os, ident_level);
      os << fmt::format(sv, std::forward<Args>(args)...);
      os << '\n';
   }

   template<typename... Args>
   void line_ignore(fmt::format_string<Args...> sv, Args... args) {
      os << fmt::format(sv, std::forward<Args>(args)...);
      os << '\n';
   }

   void line();

   template<typename... Args>
   void scope(fmt::format_string<Args...> sv, Args... args) {
      apply_indent(os, ident_level);
      os << fmt::format(sv, std::forward<Args>(args)...);
      os << " {\n";
      ident();
   }

   template<typename... Args>
   void flat_scope(fmt::format_string<Args...> sv, Args... args) {
      apply_indent(os, ident_level);
      os << fmt::format(sv, std::forward<Args...>(args)...);
      os << " {\n";
   }

   void descope();

   template<typename... Args>
   void descope(fmt::format_string<Args...> sv, Args... args) {
      deindent();
      apply_indent(os, ident_level);
      os << '}' << fmt::format(sv, std::forward<Args...>(args)...) << '\n';
   }

   void descope_flat();

   std::ostream &raw();
};

}// namespace minecpp::util
