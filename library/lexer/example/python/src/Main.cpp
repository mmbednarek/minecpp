#include "minecpp/lexer/Core.h"

#include <iostream>
#include <mb/enum.h>

enum class TokenType
{
   KeywordDef,
   KeywordPass,
   Identifier,
   Number,
   String,
   LeftParen,
   RightParen,
   Colon,
   Comma,
   Plus,
   PlusAssignment
};

struct Token
{
   TokenType type;
   std::string value;
   int line;
   int column;
};

enum class Environment
{
   Base,
   DoubleQuoteString,
   DoubleQuoteStringEscape,
   PlusSign
};

TokenType classify_stash(const std::string &stash, Environment environment)
{
   switch (environment) {
   case Environment::Base: {
      if (stash == "def") {
         return TokenType::KeywordDef;
      }
      if (stash == "pass") {
         return TokenType::KeywordPass;
      }
      return TokenType::Identifier;
   }
   case Environment::DoubleQuoteString: return TokenType::String;
   case Environment::DoubleQuoteStringEscape: return TokenType::Number;
   case Environment::PlusSign: break;
   }
   return TokenType::Comma;
}

using LexerTypes = minecpp::lexer::Types<TokenType, Token, Environment, classify_stash>;

// clang-format off

using BaseEnv = LexerTypes::FirstMatch<
   LexerTypes::OnCharFlushAndEnterEnvironment<'"', Environment::DoubleQuoteString>,
   LexerTypes::OnCharFlushAndEnterEnvironment<'+', Environment::PlusSign>,
   LexerTypes::OnCharFlushAndAddItAsToken<'(', TokenType::LeftParen>,
   LexerTypes::OnCharFlushAndAddItAsToken<')', TokenType::RightParen>,
   LexerTypes::OnCharFlushAndAddItAsToken<',', TokenType::Comma>,
   LexerTypes::OnCharFlushAndAddItAsToken<':', TokenType::Colon>,
   LexerTypes::OnCharFlushAndSkip<' '>,
   LexerTypes::OnCharFlushAndIncreaseLineNumber<'\n'>,
   LexerTypes::AddCurrentCharToStash
>;

using DoubleQuoteStringEnv = LexerTypes::FirstMatch<
   LexerTypes::OnCharFlushAndEnterEnvironment<'"', Environment::Base>,
   LexerTypes::OnCharEnterEnvironment<'\\', Environment::DoubleQuoteStringEscape>,
   LexerTypes::AddCurrentCharToStash
>;

using DoubleQuoteStringEscapeEnv = LexerTypes::Sequence<
   LexerTypes::FirstMatch<
      LexerTypes::OnCharAddToStash<'n', '\n'>,
      LexerTypes::OnCharAddToStash<'r', '\r'>
   >,
   LexerTypes::EnterEnvironment<Environment::DoubleQuoteString>
>;

using PlusSignEnv = LexerTypes::Sequence<
   LexerTypes::FirstMatch<
      LexerTypes::OnCharAddItAsToken<'=', TokenType::PlusAssignment>,
      LexerTypes::Sequence<
         LexerTypes::AddStringToken<"+=", TokenType::Plus>,
         LexerTypes::StepBack
      >
   >,
   LexerTypes::EnterEnvironment<Environment::Base>
>;

// clang-format on

class StringReader : public minecpp::lexer::IReader
{
   std::string m_data;
   std::size_t m_at{};

 public:
   explicit StringReader(std::string_view data) :
       m_data(data)
   {
   }

   bool has_next() override
   {
      return m_at < m_data.size();
   }

   char next() override
   {
      return m_data[m_at++];
   }

   void step_back() override
   {
      if (m_at == 0)
         return;
      --m_at;
   }
};

int main()
{
   auto data = R"(
def main(argv):
   a += 2+2
)";
   StringReader reader(data);

   auto lexed = minecpp::lexer::lex_from<LexerTypes, BaseEnv, DoubleQuoteStringEnv,
                                         DoubleQuoteStringEscapeEnv, PlusSignEnv>(reader);

   for (const auto &token : lexed) {
      std::cout << "(" << token.line << ":" << token.column << ") " << token.value << '\n';
   }

   return 0;
}