#ifndef MINECPP_PARSER_H
#define MINECPP_PARSER_H
#include "token.h"
#include <vector>
#include <minecpp/nbt/tag.h>
#include <mb/result.h>

namespace minecpp::tool::snbt_parser {

class TokenReader {
   const std::vector<Token> &m_tokens;
   std::size_t m_at{};
 public:
   constexpr explicit TokenReader(const std::vector<Token> &tokens) : m_tokens(tokens) {}

   Token next() {
      auto at = m_at;
      if (m_at < m_tokens.size()-1)
         ++m_at;
      return m_tokens[at];
   }

   void skip_next() {
      if (m_at < m_tokens.size()-1)
         ++m_at;
   }

   TokenType token_type()  {
      return m_tokens[m_at].type;
   }

   bool has_next() {
      return m_at < m_tokens.size();
   }
};

class Parser {
   TokenReader m_reader;
 public:
   explicit Parser(const std::vector<Token> &tokens);

   mb::result<Token> expect(TokenType type);
   mb::result<std::string> expect_identifier();

   mb::result<nbt::CompoundContent> read_compound();
   mb::result<nbt::Content> read_content();
   mb::result<nbt::ListContent> read_list();

   mb::emptyres assert_not_end();
};

}

#endif//MINECPP_PARSER_H
