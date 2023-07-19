#include "CppUtil.h"
#include "../IGenerator.h"

#include "minecpp/util/Case.h"

#include <algorithm>
#include <array>
#include <sstream>

namespace minecpp::tool::schema_compiler::generator {

namespace {

Symbol find_symbol(const Document &document, const SymbolTable &symbol_table, const Type &type)
{
   auto symbol = symbol_table.find_symbol(document.package_info().full_name(), type.full_name());
   generator_verify(symbol.has_value(), type.line(), type.column(), "could not find symbol {} in package {}",
                    type.full_name(), document.package_info().full_name());
   return *symbol;
}

}// namespace

CppType::CppType(const Document &document, const SymbolTable &symbol_table, const Type &type) :
    m_symbol{find_symbol(document, symbol_table, type)},
    m_document{document},
    m_symbol_table{symbol_table},
    m_type{type}
{
}

// clang-format off
constexpr std::array<const char *, 24> g_core_cpp_types{
        "std::int8_t",
        "std::int16_t",
        "std::int32_t",
        "std::int64_t",
        "std::uint8_t",
        "std::uint16_t",
        "std::uint32_t",
        "std::uint64_t",
        "std::string",
        "float",
        "double",
        "std::vector",
        "std::map",
        "std::map",
        "std::optional",
        "std::variant",
        "std::int32_t",
        "std::int64_t",
        "std::uint32_t",
        "std::uint64_t",
        "bool",
        "::minecpp::util::Uuid",
        "::minecpp::nbt::CompoundContent",
        ""
};

// clang-format on

namespace {

/*
 This functions looks for dots
 of 2 packages and checks their common part.
 */
std::size_t common_package_part(std::string_view left, std::string_view right)
{
   std::size_t result{0};

   while (result != std::string_view::npos) {
      auto left_dot  = left.find('.', result + 1);
      auto right_dot = right.find('.', result + 1);

      if (left_dot != right_dot)
         return result;
      if (left.substr(0, left_dot) != right.substr(0, right_dot))
         return result;

      result = left_dot;
   }

   return left.size();
}

std::string construct_cpp_namespace(const std::size_t start_at, std::string_view package_name)
{
   if (package_name.size() <= start_at)
      return {};

   std::stringstream ss;
   std::for_each(package_name.begin() + start_at, package_name.end(), [&ss](char ch) {
      if (ch == '.') {
         ss << "::";
         return;
      }
      ss << ch;
   });

   return ss.str();
}

}// namespace

std::string CppType::type_name() const
{
   if (m_symbol.type_class != TypeClass::Record) {
      auto &cpp_type = g_core_cpp_types[static_cast<std::size_t>(m_symbol.type_class)];
      if (m_type.template_args_count() == 0) {
         return cpp_type;
      }

      std::stringstream ss;
      ss << cpp_type << '<';

      bool is_first = true;
      for (std::size_t i{}; i < m_type.template_args_count(); ++i) {
         if (is_first) {
            is_first = false;
         } else {
            ss << ", ";
         }

         const auto &sub_type = m_type.template_arg_at(i);
         generator_verify(sub_type.has_value(), sub_type->line(), sub_type->column(),
                          "internal error: invalid template argument count");

         CppType cpp_sub_type(m_document, m_symbol_table, *sub_type);
         ss << cpp_sub_type.type_name();
      }
      ss << '>';

      return ss.str();
   }

   generator_verify(m_type.template_args_count() == 0, m_type.line(), m_type.column(),
                    "record shouldn't have template arguments");

   auto package_name = m_document.package_info().full_name();
   auto common_at    = common_package_part(m_symbol.package, package_name);

   auto namespace_name = construct_cpp_namespace(common_at + 1, m_symbol.package);
   if (namespace_name.empty())
      return m_type.name();

   return fmt::format("{}::{}", namespace_name, m_type.name());
}

const Symbol &CppType::symbol() const
{
   return m_symbol;
}

CppAttribute::CppAttribute(const Document &document, const SymbolTable &symbol_table,
                           const Attribute &attribute) :
    m_cpp_type(document, symbol_table, attribute.type()),
    m_attribute{attribute}
{
}

std::string CppAttribute::type_name() const
{
   return m_cpp_type.type_name();
}

std::string CppAttribute::name() const
{
   if (m_attribute.annotations().has_key("CC_Name")) {
      return m_attribute.annotations().value_at("CC_Name");
   }

   std::string result;
   util::convert_to_snake_case(m_attribute.name().begin(), m_attribute.name().end(),
                               std::back_inserter(result));

   return result;
}

TypeClass CppAttribute::type_class() const
{
   return m_cpp_type.symbol().type_class;
}

}// namespace minecpp::tool::schema_compiler::generator
