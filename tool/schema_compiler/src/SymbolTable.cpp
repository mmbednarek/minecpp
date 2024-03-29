#include "SymbolTable.h"

#include <fmt/core.h>

namespace minecpp::tool::schema_compiler {

void SymbolTable::read_document(std::string_view source_file, const Document &document)
{
   auto package_name = document.package_info().full_name();

   for (const auto &record : document.records()) {
      this->register_symbol(Symbol{
              .type_class = TypeClass::Record,
              .name{record.name()},
              .package{package_name},
              .source_file{std::string{source_file}},
              .generator{document.generator()},
              .annotations{record.annotations()},
      });
   }
}

void SymbolTable::read_document_for_aliases(std::string_view source_file, const Document &document)
{
   auto package_name = document.package_info().full_name();


   for (const auto &alias : document.aliases()) {
      auto symbol = this->find_symbol(package_name, alias.aliased_type().full_name());
      if (not symbol.has_value())
         throw std::runtime_error(fmt::format("symbol {} is not found", alias.aliased_type().full_name()));

      this->register_symbol(Symbol{
              .type_class = symbol->type_class,
              .name{alias.name()},
              .package{package_name},
              .source_file{std::string{source_file}},
              .generator{symbol->generator},
              .annotations{alias.annotations()},
      });
   }
}

std::optional<Symbol> SymbolTable::find_symbol(std::string_view package, std::string_view name) const
{
   while (not package.empty()) {
      auto symbol = fmt::format("{}.{}", package, name);
      auto it     = m_symbol_list.find(symbol);
      if (it != m_symbol_list.end()) {
         return it->second;
      }

      auto dot_at = package.find_last_of('.');
      if (dot_at == std::string_view::npos)
         package = {};

      package = package.substr(0, dot_at);
   }

   auto it = m_symbol_list.find(std::string{name});
   return (it == m_symbol_list.end()) ? std::nullopt : std::optional<Symbol>{it->second};
}

void SymbolTable::register_symbol(const Symbol &symbol)
{
   if (symbol.package.empty()) {
      m_symbol_list.emplace(symbol.name, symbol);
      return;
   }

   auto symbol_id = fmt::format("{}.{}", symbol.package, symbol.name);
   if (m_symbol_list.contains(symbol_id)) {
      throw std::runtime_error(fmt::format("symbol {} is already registered", symbol_id));
   }

   m_symbol_list.emplace(symbol_id, symbol);
}

}// namespace minecpp::tool::schema_compiler
