#pragma once
#include "Token.h"
#include <mb/result.h>
#include <vector>

namespace Lex {

class TokenReader
{
 public:
   explicit TokenReader(std::vector<Token> elements);

   Token next();
   Token expect(TokenType t);
   void back();

 private:
   std::vector<Token> m_elements;
   std::size_t m_at{};
};

}// namespace Lex