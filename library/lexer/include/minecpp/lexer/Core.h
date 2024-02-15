#pragma once

#include "IReader.h"

#include <cassert>
#include <mb/compile_time.h>
#include <string>
#include <string_view>
#include <vector>

namespace minecpp::lexer {

template<typename TTypes>
class Context
{
 public:
   explicit Context(IReader &reader) :
       m_reader(reader)
   {
   }

   void add_token(const std::string_view value, typename TTypes::TokenType token_type)
   {
      m_tokens.push_back(typename TTypes::Token{token_type, std::string{value}, m_line, m_column});
   }

   void push_identifier()
   {
      if (m_identifier.empty())
         return;
      m_tokens.push_back(typename TTypes::Token{TTypes::classify_callback(m_identifier, m_environment),
                                                m_identifier, m_line,
                                                m_column - static_cast<int>(m_identifier.size())});
      m_identifier.clear();
   }

   void add_single_char_token(const char ch, typename TTypes::TokenType token_type)
   {
      m_tokens.push_back(typename TTypes::Token{
              token_type, std::string{&ch, 1},
               m_line, m_column
      });
   }

   void enter_environment(typename TTypes::Environment environment)
   {
      m_environment = environment;
   }

   void append_to_identifier(const char ch)
   {
      m_identifier.push_back(ch);
   }

   void increase_line()
   {
      m_column = 0;
      ++m_line;
   }

   void increase_column()
   {
      ++m_column;
   }

   [[nodiscard]] typename TTypes::Environment environment() const
   {
      return m_environment;
   }

   std::vector<typename TTypes::Token> take_tokens()
   {
      return std::move(m_tokens);
   }

   void step_back()
   {
      m_reader.step_back();
   }

 private:
   IReader &m_reader;
   typename TTypes::Environment m_environment{};
   std::vector<typename TTypes::Token> m_tokens;
   std::string m_identifier;
   int m_line{1};
   int m_column{1};
};

template<typename TTypes, char CCondition, typename TRule>
struct Rule_OnChar
{
   static bool run(const char ch, typename TTypes::TypeContext &ctx)
   {
      if (ch == CCondition)
         return TRule::run(ch, ctx);
      return false;
   }
};

template<typename TTypes, typename TTypes::Environment CTargetEnvironment>
struct Rule_EnterEnvironment
{
   static bool run(const char /*ch*/, typename TTypes::TypeContext &ctx)
   {
      ctx.enter_environment(CTargetEnvironment);
      return true;
   }
};

template<typename TTypes>
struct Rule_AddCurrentCharToStash
{
   static bool run(const char ch, typename TTypes::TypeContext &ctx)
   {
      ctx.append_to_identifier(ch);
      return true;
   }
};

template<typename TTypes, char CCharToAppend>
struct Rule_AddToStash
{
   static bool run(const char /*ch*/, typename TTypes::TypeContext &ctx)
   {
      ctx.append_to_identifier(CCharToAppend);
      return true;
   }
};

template<typename TTypes, typename TFirstRule, typename... TOtherRules>
struct Rule_Sequence
{
   static bool run(const char ch, typename TTypes::TypeContext &ctx)
   {
      if (not TFirstRule::run(ch, ctx))
         return false;

      if constexpr (sizeof...(TOtherRules) > 0) {
         return Rule_Sequence<TTypes, TOtherRules...>::run(ch, ctx);
      } else {
         return true;
      }
   }
};

template<typename TTypes>
struct Rule_FlushStash
{
   static bool run(const char /*ch*/, typename TTypes::TypeContext &ctx)
   {
      ctx.push_identifier();
      return true;
   }
};

template<typename TTypes, char CChar, typename TTypes::TokenType CTokenType>
struct Rule_AddCharToken
{
   static bool run(const char /*ch*/, typename TTypes::TypeContext &ctx)
   {
      ctx.add_single_char_token(CChar, CTokenType);
      return true;
   }
};

template<typename TTypes>
struct Rule_IncreaseLineNumber
{
   static bool run(const char /*ch*/, typename TTypes::TypeContext &ctx)
   {
      ctx.increase_line();
      return true;
   }
};

template<typename TTypes>
struct Rule_Skip
{
   static bool run(const char /*ch*/, typename TTypes::TypeContext & /*ctx*/)
   {
      return true;
   }
};

template<typename TTypes>
struct Rule_StepBack
{
   static bool run(const char /*ch*/, typename TTypes::TypeContext &ctx)
   {
      ctx.step_back();
      return true;
   }
};

template<typename TTypes, mb::const_string CValue, typename TTypes::TokenType CTokenType>
struct Rule_AddStringToken
{
   static bool run(const char /*ch*/, typename TTypes::TypeContext &ctx)
   {
      ctx.add_token(CValue.to_string_view(), CTokenType);
      return true;
   }
};

template<typename TTypes, typename TFirstRule, typename... TOtherRules>
struct Rule_FirstMatch
{
   static bool run(const char ch, typename TTypes::TypeContext &ctx)
   {
      if (TFirstRule::run(ch, ctx))
         return true;

      if constexpr (sizeof...(TOtherRules) > 0) {
         return Rule_FirstMatch<TTypes, TOtherRules...>::run(ch, ctx);
      } else {
         return false;
      }
   }
};

template<typename TTokenType, typename TToken, typename TEnvironmentEnum, auto CClassifyCallback>
struct Types
{
   using Self                              = Types;
   using TokenType                         = TTokenType;
   using Token                             = TToken;
   using Environment                       = TEnvironmentEnum;
   using TypeContext                           = Context<Self>;
   static constexpr auto classify_callback = CClassifyCallback;

   template<typename... TRules>
   using FirstMatch = Rule_FirstMatch<Self, TRules...>;

   template<char CCondition, typename TRule>
   using OnChar = Rule_OnChar<Self, CCondition, TRule>;

   template<typename... TRules>
   using Sequence = Rule_Sequence<Self, TRules...>;

   using FlushStash = Rule_FlushStash<Self>;

   template<TEnvironmentEnum CTargetEnvironment>
   using EnterEnvironment = Rule_EnterEnvironment<Self, CTargetEnvironment>;

   template<TEnvironmentEnum CTargetEnvironment>
   using FlushAndEnterEnvironment = Sequence<FlushStash, EnterEnvironment<CTargetEnvironment>>;

   template<char CCondition, TEnvironmentEnum CTargetEnvironment>
   using OnCharEnterEnvironment = OnChar<CCondition, EnterEnvironment<CTargetEnvironment>>;

   template<char CCondition, TEnvironmentEnum CTargetEnvironment>
   using OnCharFlushAndEnterEnvironment = OnChar<CCondition, FlushAndEnterEnvironment<CTargetEnvironment>>;

   using AddCurrentCharToStash = Rule_AddCurrentCharToStash<Self>;

   template<char CCharToAppend>
   using AddToStash = Rule_AddToStash<Self, CCharToAppend>;

   template<char CChar, char CCharToAppend>
   using OnCharAddToStash = OnChar<CChar, AddToStash<CCharToAppend>>;

   template<char CChar, TokenType CTokenType>
   using AddCharToken = Rule_AddCharToken<Self, CChar, CTokenType>;

   template<char CChar, TokenType CTokenType>
   using FlushAndAddCharToken = Sequence<FlushStash, AddCharToken<CChar, CTokenType>>;

   template<char CChar, TokenType CTokenType>
   using OnCharFlushAndAddItAsToken = OnChar<CChar, FlushAndAddCharToken<CChar, CTokenType>>;

   template<char CChar, TokenType CTokenType>
   using OnCharAddItAsToken = OnChar<CChar, AddCharToken<CChar, CTokenType>>;

   using IncreaseLineNumber = Rule_IncreaseLineNumber<Self>;

   using FlushAndIncreaseLineNumber = Sequence<FlushStash, IncreaseLineNumber>;

   template<char CChar>
   using OnCharFlushAndIncreaseLineNumber = OnChar<CChar, FlushAndIncreaseLineNumber>;

   using Skip = Rule_Skip<Self>;

   template<char CChar>
   using IgnoreChar = OnChar<CChar, Skip>;

   template<char CChar>
   using OnCharFlushAndSkip = OnChar<CChar, Sequence<FlushStash, Skip>>;

   using StepBack = Rule_StepBack<Self>;

   template<mb::const_string CValue, TokenType CTokenType>
   using AddStringToken = Rule_AddStringToken<Self, CValue, CTokenType>;
};

template<typename TTypes, typename TFirstEnvironmentRule, typename... TEnvironmentRules>
struct EnvironmentSelector
{
   int index{};

   bool run(const char ch, typename TTypes::TypeContext &ctx)
   {
      if (index == 0) {
         return TFirstEnvironmentRule::run(ch, ctx);
      }
      if constexpr (sizeof...(TEnvironmentRules) > 0) {
         return EnvironmentSelector<TTypes, TEnvironmentRules...>{index - 1}.run(ch, ctx);
      } else {
         return false;
      }
   }
};

template<typename TTypes, typename... TEnvironmentRules>
std::vector<typename TTypes::Token> lex_from(IReader &reader)
{
   typename TTypes::TypeContext context(reader);

   while (reader.has_next()) {
      auto ch  = reader.next();
      auto env = static_cast<int>(context.environment());

      auto result = EnvironmentSelector<TTypes, TEnvironmentRules...>{env}.run(ch, context);
      assert(result);
      (void) result;

      context.increase_column();
   }
   context.push_identifier();

   return context.take_tokens();
}

}// namespace minecpp::lexer