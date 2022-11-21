#ifndef MINECPP_TOKEN_H
#define MINECPP_TOKEN_H
#include <string>

namespace minecpp::tool::snbt_parser {

enum class TokenType
{
   Identifier,
   String,
   Byte,
   Short,
   Int,
   Long,
   Float,
   Double,
   Colon,
   Comma,
   LeftBrace,
   RightBrace,
   LeftSquareBracket,
   RightSquareBracket,
};

struct Token
{
   TokenType type;
   std::string value;
};

}// namespace minecpp::tool::snbt_parser

#endif//MINECPP_TOKEN_H
