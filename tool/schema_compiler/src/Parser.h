#pragma once

#include "Ast.h"
#include "Lexer.h"

#include "minecpp/lexer/TokenFeed.h"

#include <mb/enum.h>
#include <mb/result.h>

namespace minecpp::tool::schema_compiler {

enum class ParserErrorValue
{
   MissingPackageKeyword,
   UnexpectedToken,
};

// clang-format off

using ParserError_Base = mb::enum_wrapper<ParserErrorValue,
   "missing keyword package",
   "unexpected token"
>;

// clang-format on

class ParserError : public ParserError_Base
{
 public:
   MB_ENUM_TRAITS(ParserError)

   MB_ENUM_FIELD(MissingPackageKeyword)
   MB_ENUM_FIELD(UnexpectedToken)

   int line{};
   int column{};
};

ParserError make_parser_error(ParserErrorValue value, int line, int column);

template<typename TType>
using Result = mb::result<TType, ParserError>;

class Parser
{
 public:
   explicit Parser(const std::vector<Token> &tokens);

   Result<Document> parse_document();
   Result<PackageInfo> parse_package_info();
   Result<Import> parse_import();
   Result<Record> parse_record();
   Result<AnnotationList> parse_annotation_list();
   Result<Attribute> parse_attribute();
   Result<Type> parse_type();

   void skip_new_lines();

 private:
   lexer::TokenFeed<Token, TokenType> m_token_feed;
};

}// namespace minecpp::tool::schema_compiler