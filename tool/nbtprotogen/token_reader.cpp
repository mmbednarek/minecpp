#include "token_reader.h"
#include <fmt/core.h>

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

mb::result<Token> TokenReader::expect(TokenType t) {
   auto tkn = next();
   if (tkn.tt != t) {
      return mb::error(fmt::format("[{}:{}] unexpected token \"{}\"", tkn.line, tkn.col, tkn.value));
   }
   return tkn;
}

void TokenReader::back() {
   --at;
   if (at < 0) at = 0;
}

}// namespace Lex
