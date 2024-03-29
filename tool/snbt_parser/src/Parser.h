#ifndef MINECPP_PARSER_H
#define MINECPP_PARSER_H
#include "Token.h"
#include <mb/result.h>
#include <minecpp/nbt/Tag.h>
#include <vector>

namespace minecpp::tool::snbt_parser {

class TokenReader
{
   const std::vector<Token> &m_tokens;
   std::size_t m_at{};

 public:
   constexpr explicit TokenReader(const std::vector<Token> &tokens) :
       m_tokens(tokens)
   {
   }

   Token next()
   {
      auto at = m_at;
      if (m_at < m_tokens.size() - 1)
         ++m_at;
      return m_tokens[at];
   }

   void skip_next()
   {
      if (m_at < m_tokens.size() - 1)
         ++m_at;
   }

   TokenType token_type()
   {
      return m_tokens[m_at].type;
   }

   bool has_next()
   {
      return m_at < m_tokens.size();
   }
};

class Parser
{
   TokenReader m_reader;

 public:
   explicit Parser(const std::vector<Token> &tokens);

   Token expect(TokenType type);
   std::string expect_identifier();

   nbt::CompoundContent read_compound();
   nbt::Content read_content();
   nbt::ListContent read_list();

   void assert_not_end();
};

}// namespace minecpp::tool::snbt_parser

#endif//MINECPP_PARSER_H
