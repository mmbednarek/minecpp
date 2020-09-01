#include "token_reader.h"

namespace Lex {

TokenReader::TokenReader(std::vector<Token> elements) : elements(std::move(elements)) {
}

Token TokenReader::next() {
   if (at >= elements.size()) {
      return Token{
              .tt = TokenType::Eof,
      };
   }
   return elements[at++];
}

result<Token> TokenReader::expect(TokenType t) {
   auto tkn = next();
   if (tkn.tt != t) {
      return errorf("[{}:{}] unexpected token \"{}\"", tkn.line, tkn.col, tkn.value);
   }
   return tkn;
}

void TokenReader::back() {
   --at;
   if (at < 0) at = 0;
}

}// namespace Lex
