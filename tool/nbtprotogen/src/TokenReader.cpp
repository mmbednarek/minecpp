#include "TokenReader.h"
#include "Error.h"

namespace Lex {

using minecpp::tool::nbt_idl::Error;
using minecpp::tool::nbt_idl::ErrorType;

TokenReader::TokenReader(std::vector<Token> elements) :
    m_elements(std::move(elements))
{
}

Token TokenReader::next()
{
   if (m_at >= m_elements.size()) {
      return Token{
              .tt = TokenType::Eof,
      };
   }
   return m_elements[m_at++];
}

Token TokenReader::expect(TokenType t)
{
   auto tkn = next();
   if (tkn.tt != t) {
      throw Error(tkn.line, tkn.col, ErrorType::UnexpectedToken, "");
   }
   return tkn;
}

void TokenReader::back()
{
   if (m_at == 0)
      return;

   --m_at;
}

}// namespace Lex
