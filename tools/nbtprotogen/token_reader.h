#pragma once
#include <vector>
#include <error/result.h>
#include "token.h"

namespace Lex {

class TokenReader {
   std::vector<Token> elements;
   std::size_t at = 0;
 public:
   explicit TokenReader(std::vector<Token> elements);

   Token next();
   result<Token> expect(TokenType t);
   void back();
};

}