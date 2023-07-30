#pragma once

#include "../Ast.h"
#include "NetworkPropertyStorage.h"

#include <mb/codegen/statement.h>

namespace minecpp::tool::schema_compiler::generator {

class NetworkSerializeContext
{
 public:
   NetworkSerializeContext(Type type, std::string_view name, const mb::codegen::expression &source_expression,
                           AnnotationList annotations, int depth,
                           mb::codegen::statement::collector &collector,
                           NetworkPropertyStorage &property_storage, const SymbolTable &symbol_table,
                           const Document &document);

   [[nodiscard]] const AnnotationList &annotations() const;
   const mb::codegen::expression &source_property();
   mb::codegen::statement::collector &collector();

   [[nodiscard]] std::string unique_name(std::string_view suffix) const;

   [[nodiscard]] const Type &type() const;
   [[nodiscard]] std::string type_generator() const;
   [[nodiscard]] TypeClass type_class() const;
   [[nodiscard]] Symbol symbol() const;

   void write_serializer(const Type &type, const mb::codegen::expression &source_expression,
                         std::string_view name, mb::codegen::statement::collector &collector);

   mb::codegen::statement::collector &operator<<(const mb::codegen::statement &stmt);
   mb::codegen::statement::collector &operator<<(const mb::codegen::expression &expre);

 private:
   Type m_type;
   std::string m_name;
   std::unique_ptr<mb::codegen::expression> m_source_property;
   AnnotationList m_annotations;
   int m_depth;
   mb::codegen::statement::collector &m_collector;
   NetworkPropertyStorage &m_property_storage;
   const SymbolTable &m_symbol_table;
   const Document &m_document;
};

}// namespace minecpp::tool::schema_compiler::generator
