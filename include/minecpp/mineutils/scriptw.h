#pragma once
#include "string.h"
#include <cstdint>
#include <fmt/core.h>
#include <ostream>

namespace Utils {

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
   void line(std::string_view sv, Args... args) {
      apply_indent(os, ident_level);
      os << fmt::format(sv, args...);
      os << '\n';
   }

   template<typename... Args>
   void line_ignore(std::string_view sv, Args... args) {
      os << fmt::format(sv, args...);
      os << '\n';
   }

   void line();

   template<typename... Args>
   void scope(std::string_view sv, Args... args) {
      apply_indent(os, ident_level);
      os << fmt::format(sv, args...);
      os << " {\n";
      ident();
   }

   template<typename... Args>
   void flat_scope(std::string_view sv, Args... args) {
      apply_indent(os, ident_level);
      os << fmt::format(sv, args...);
      os << " {\n";
   }

   void descope();

   template<typename... Args>
   void descope(std::string_view sv, Args... args) {
      deindent();
      apply_indent(os, ident_level);
      os << '}' << fmt::format(sv, args...) << '\n';
   }

   void descope_flat();

   std::ostream &raw();
};

}// namespace Utils
