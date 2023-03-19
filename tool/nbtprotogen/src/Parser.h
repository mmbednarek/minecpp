#pragma once
#include "Ast.h"
#include "TokenReader.h"
#include <mb/result.h>

namespace Syntax {

class Parser
{
   Lex::TokenReader &reader;

 public:
   explicit Parser(Lex::TokenReader &reader);

   std::vector<Ast::Node> parse();

 private:
   Ast::SyntaxInfo parse_syntax_info(Ast::Location loc);
   Ast::PackageInfo parse_package_info(Ast::Location loc);
   Ast::Message parse_message(Ast::Location loc);
   Ast::Attribute parse_attribute(Ast::Location loc);
   Ast::Import parse_import(Ast::Location loc);
};

}// namespace Syntax