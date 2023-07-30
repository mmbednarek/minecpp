#pragma once

#include "../Ast.h"
#include "../SymbolTable.h"

namespace minecpp::tool::schema_compiler::generator {

class CppType
{
 public:
   CppType(const Document &document, const SymbolTable &symbol_table, const Type &type);

   [[nodiscard]] std::string type_name() const;
   [[nodiscard]] const Symbol &symbol() const;

 private:
   Symbol m_symbol;
   const Document &m_document;
   const SymbolTable &m_symbol_table;
   const Type &m_type;
};

class CppAttribute
{
 public:
   CppAttribute(const Document &document, const SymbolTable &symbol_table, const Attribute &attribute);

   [[nodiscard]] std::string type_name() const;
   [[nodiscard]] std::string name() const;
   [[nodiscard]] TypeClass type_class() const;

 private:
   CppType m_cpp_type;
   const Attribute &m_attribute;
};

}// namespace minecpp::tool::schema_compiler::generator
