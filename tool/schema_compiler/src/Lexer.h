#pragma once

#include <string>
#include <istream>
#include <vector>

namespace minecpp::tool::schema_compiler {

enum class TokenType {
   KeywordPackage,
   KeywordImport,
   KeywordRecord,
   Identifier,
   String,
   LeftBracket,
   RightBracket,
   LeftSquareBracket,
   RightSquareBracket,
   EqualSign,
   Colon,
   Comma,
   Dot,
   NewLine
};

struct Token {
   TokenType type;
   std::string value;
   int line;
   int column;
};

std::vector<Token> lex_input(std::istream &input);

}// namespace minecpp::tool::schema_compiler