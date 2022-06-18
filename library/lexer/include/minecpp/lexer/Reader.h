#ifndef MINECPP_READER_H
#define MINECPP_READER_H
#include "Error.h"
#include "Token.h"
#include <optional>
#include <vector>

namespace minecpp::lexer {

class TokenReader
{
 public:
   using iterator   = std::vector<lexer::Token>::const_iterator;
   using value_type = lexer::Token;

   explicit TokenReader(const std::vector<lexer::Token> &tokens) :
       m_beg(tokens.begin()),
       m_at(tokens.begin()),
       m_end(tokens.end())
   {
   }

   [[nodiscard]] constexpr std::optional<const value_type> next()
   {
      if (m_at == m_end) {
         return std::nullopt;
      }
      return *(m_at++);
   }

   constexpr void seek_back()
   {
      if (m_at == m_beg)
         return;
      --m_at;
   }

 private:
   iterator m_beg, m_at, m_end;
};

}// namespace minecpp::lexer

#endif//MINECPP_READER_H
