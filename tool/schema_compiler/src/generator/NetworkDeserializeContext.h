#pragma once

#include "../Ast.h"
#include "../SymbolTable.h"
#include "NetworkPropertyStorage.h"

#include <mb/codegen/statement.h>
#include <memory>

namespace minecpp::tool::schema_compiler::generator {

class NetworkDeserializeContext
{
 public:
   NetworkDeserializeContext(Type type, std::string name,
                             std::unique_ptr<mb::codegen::expression> m_destination,
                             AnnotationList m_annotations, int depth,
                             mb::codegen::statement::collector &collector,
                             NetworkPropertyStorage &property_storage, const SymbolTable &symbol_table,
                             const Document &document);

   [[nodiscard]] const Type &type() const;
   [[nodiscard]] std::string type_name() const;
   [[nodiscard]] const AnnotationList &annotations() const;
   [[nodiscard]] std::string type_generator() const;
   [[nodiscard]] TypeClass type_class() const;
   [[nodiscard]] Symbol symbol() const;

   void assign_expression(const mb::codegen::expression &expression);
   std::string unique_name(std::string_view suffix);

   void ensure_destination();
   [[nodiscard]] const mb::codegen::expression &destination() const;

   void write_deserializer(const Type &type, mb::codegen::statement::collector &collector,
                           const std::string &name, const mb::codegen::expression &destination);
   std::unique_ptr<mb::codegen::expression> write_deserializer(const Type &type,
                                                               mb::codegen::statement::collector &collector,
                                                               const std::string &name);
   std::unique_ptr<mb::codegen::expression>
   write_deserializer_to_var(const Type &type, mb::codegen::statement::collector &collector,
                             const std::string &name);

   mb::codegen::statement::collector &operator<<(const mb::codegen::statement &stmt);
   mb::codegen::statement::collector &operator<<(const mb::codegen::expression &expre);

 private:
   Type m_type;
   std::string m_name;
   std::unique_ptr<mb::codegen::expression> m_destination;
   AnnotationList m_annotations;
   int m_depth;
   mb::codegen::statement::collector &m_collector;
   NetworkPropertyStorage &m_property_storage;
   const SymbolTable &m_symbol_table;
   const Document &m_document;
};

}// namespace minecpp::tool::schema_compiler::generator
