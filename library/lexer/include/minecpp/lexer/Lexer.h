#ifndef MINECPP_LEXER_H
#define MINECPP_LEXER_H
#include "Token.h"
#include <istream>
#include <vector>

namespace minecpp::lexer {

class Reader
{
 public:
   virtual bool has_next() = 0;
   virtual char next()     = 0;
};

class StringReader : public Reader
{
   std::string m_data;
   std::size_t m_at{};

 public:
   explicit StringReader(std::string_view);

   bool has_next() override;
   char next() override;
};

class Lexer
{
   enum class State
   {
      Normal,
      String,
      StringEscape,
   };

   Reader &m_reader;
   std::string m_identifier;
   std::vector<Token> m_result;
   State m_state = State::Normal;

 public:
   explicit Lexer(Reader &reader);

   std::vector<Token> lex();

 private:
   void push_identifier();
   void push_special_token(TokenType type);
};

}// namespace minecpp::lexer

#endif//MINECPP_LEXER_H
