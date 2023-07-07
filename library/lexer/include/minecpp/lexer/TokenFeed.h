#pragma once

#include <vector>
#include <optional>

namespace minecpp::lexer {

template<typename TToken, typename TTokenType>
class TokenFeed
{
 public:
   explicit TokenFeed(std::vector<TToken> elements) :
       m_tokens{std::move(elements)}
   {
   }

   std::optional<TToken> next()
   {
      if (m_at >= m_tokens.size()) {
         return std::nullopt;
      }
      return m_tokens[m_at++];
   }

   std::optional<TToken> expect(TTokenType type)
   {
      auto token = this->next();
      if (not token.has_value())
         return std::nullopt;

      if (token->type != type) {
         return std::nullopt;
      }
      return token;
   }

   void step_back()
   {
      if (m_at == 0)
         return;
      --m_at;
   }

 private:
   std::vector<TToken> m_tokens;
   std::size_t m_at{};
};

}