#pragma once
#include "token_reader.h"
#include "ast.h"
#include <mb/result.h>

namespace Syntax {

class Parser {
   Lex::TokenReader &reader;
 public:
   explicit Parser(Lex::TokenReader &reader);

   mb::result<std::vector<Ast::Node>> parse();

 private:
   mb::result<Ast::SyntaxInfo> parse_syntax_info(Ast::Location loc);
   mb::result<Ast::PackageInfo> parse_package_info(Ast::Location loc);
   mb::result<Ast::Message> parse_message(Ast::Location loc);
   mb::result<Ast::Attribute> parse_attribute(Ast::Location loc);

};

}