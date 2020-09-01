#pragma once
#include <string>

namespace Lex {

enum class TokenType {
   Eof,
   Identifier,
   Integer,
   String,
   Syntax,
   Package,
   Message,
   EqualSign,
   SemiCol,
   LeftBrace,
   RightBrace,
   LeftSquare,
   RightSquare,
   Dot
};

struct Token {
   std::string value{};
   TokenType tt{};
   int line{}, col{};
};

}