#include "TokenReader.h"
#include "Error.h"

namespace Lex {

using minecpp::tool::nbt_idl::Error;
using minecpp::tool::nbt_idl::ErrorType;

TokenReader::TokenReader(std::vector<Token> elements) :
    elements(std::move(elements))
{
}

Token TokenReader::next()
{
   if (at >= elements.size()) {
      return Token{
              .tt = TokenType::Eof,
      };
   }
   return elements[at++];
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
   --at;
   if (at < 0)
      at = 0;
}

}// namespace Lex
