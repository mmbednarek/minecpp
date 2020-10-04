#pragma once
#include "token_reader.h"
#include "ast.h"

namespace Syntax {

class Parser {
   Lex::TokenReader &reader;
 public:
   explicit Parser(Lex::TokenReader &reader);

   result<std::vector<Ast::Node>> parse();

 private:
   result<Ast::SyntaxInfo> parse_syntax_info(Ast::Location loc);
   result<Ast::PackageInfo> parse_package_info(Ast::Location loc);
   result<Ast::Message> parse_message(Ast::Location loc);
   result<Ast::Attribute> parse_attribute(Ast::Location loc);

};

}