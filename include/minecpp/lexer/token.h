#ifndef MINECPP_TOKEN_H
#define MINECPP_TOKEN_H
#include <string>

namespace minecpp::lexer {

enum class TokenType
{
   Identifier,
   Variable,
   DollarSign,
   String,
   Byte,
   Short,
   Int,
   Long,
   Float,
   Double,
   Colon,
   Comma,
   LeftParen,
   RightParen,
   LeftBrace,
   RightBrace,
   LeftSquareBracket,
   RightSquareBracket,
};

struct Token
{
   TokenType type;
   std::string value;
   int line, column;
};

}// namespace minecpp::lexer

#endif//MINECPP_TOKEN_H
