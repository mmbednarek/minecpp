#pragma once

#include <optional>
#include <vector>

namespace minecpp::lexer {

class ParserError : public std::runtime_error
{
 public:
   template<typename... TArgs>
   ParserError(int line, int column, fmt::format_string<TArgs...> format_string, TArgs &&...args) :
       std::runtime_error(fmt::format("[{}:{}] {}", line, column,
                                      fmt::format(format_string, std::forward<TArgs>(args)...)))
   {
   }
};

template<typename TFirst, typename... TArgs>
bool any_of(TFirst actual, TFirst first_expected, TArgs... other_expected)
{
   if (first_expected == actual)
      return true;

   if constexpr (sizeof...(TArgs) > 0) {
      return any_of(actual, other_expected...);
   } else {
      return false;
   }
}

template<typename TFirst, typename... TArgs>
std::string format_args_internal(std::string &output, TFirst actual, TArgs... args)
{
   fmt::format_to(std::back_inserter(output), ", {}", actual);
   if constexpr (sizeof...(args)) {
      format_args_internal(output, args...);
   }
   return output;
}

template<typename TFirst, typename... TArgs>
std::string format_args(TFirst actual, TArgs... args)
{
   std::string output;
   fmt::format_to(std::back_inserter(output), "{}", actual);
   if constexpr (sizeof...(args)) {
      format_args_internal(output, args...);
   }
   return output;
}

template<typename TToken, typename TTokenType>
class TokenFeed
{
 public:
   explicit TokenFeed(std::vector<TToken> elements) :
       m_tokens{std::move(elements)}
   {
   }

   [[nodiscard]] bool has_next() const
   {
      return m_at < m_tokens.size();
   }

   std::optional<TToken> next_opt()
   {
      if (not this->has_next())
         return std::nullopt;

      return m_tokens[m_at++];
   }

   TToken next()
   {
      auto token = this->next_opt();
      if (not token.has_value()) {
         throw ParserError(-1, -1, "unexpected end of stream");
      }
      return *token;
   }

   template<typename... TArgs>
   TToken expect(TArgs... expected)
   {
      auto token = this->next();
      if (not any_of(token.type, expected...)) {
         if constexpr (sizeof...(expected) == 1) {
            throw ParserError(token.line, token.column, "unexpected token {}, expected {}", token.type,
                              expected...);
         } else {
            throw ParserError(token.line, token.column, "unexpected token {}, expected one of: {}",
                              token.type, format_args(expected...));
         }
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

}// namespace minecpp::lexer