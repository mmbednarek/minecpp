#pragma once

#include "Ast.h"
#include "Lexer.h"

#include "minecpp/lexer/TokenFeed.h"

#include <fmt/core.h>
#include <mb/enum.h>
#include <mb/result.h>

namespace minecpp::tool::schema_compiler {

class Parser
{
 public:
   explicit Parser(const std::vector<Token> &tokens);

   Document parse_document();
   PackageInfo parse_package_info();
   GeneratorInfo parse_generator_info();
   Import parse_import();
   Record parse_record();
   AnnotationList parse_annotation_list();
   Attribute parse_attribute();
   Type parse_type();

   void skip_new_lines();

 private:
   lexer::TokenFeed<Token, TokenType> m_token_feed;
};

}// namespace minecpp::tool::schema_compiler