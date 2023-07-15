#pragma once

#include "Ast.h"

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::tool::schema_compiler {

enum class TypeClass
{
   Int8,
   Int16,
   Int32,
   Int64,
   UInt8,
   UInt16,
   UInt32,
   UInt64,
   String,
   Float32,
   Float64,
   List,
   Map,
   Record,
   Optional,
   Variant,
   Varint,
   Varlong,
   Uuid,
   NbtCompoundContent,
   Unknown
};

struct Symbol
{
   TypeClass type_class;
   std::string name;
   std::string package;
   std::string source_file;
   std::string generator;
   AnnotationList annotations;
};

class SymbolTable
{
 public:
   void read_document(std::string_view source_file, Document &document);
   [[nodiscard]] std::optional<Symbol> find_symbol(std::string_view package, std::string_view name) const;
   void register_symbol(const Symbol &symbol);

 private:
   std::map<std::string, Symbol> m_symbol_list;
};

}// namespace minecpp::tool::schema_compiler