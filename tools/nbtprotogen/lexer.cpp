#include "lexer.h"
#include "lex.yy.h"

extern std::vector<Lex::Token> lex_output;

namespace Lex {

TokenReader lex(std::istream &stream) {
    std::stringstream ss;
   lex_output.clear();
   FlexLexer *lexer = new yyFlexLexer;
   while (lexer->yylex(stream, ss) != 0)
      ;

   std::vector<Token> lex(lex_output.size());
   std::copy(lex_output.begin(), lex_output.end(), lex.begin());
   return TokenReader(lex);
}

}// namespace Lex
