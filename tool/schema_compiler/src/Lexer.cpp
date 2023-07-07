#include "Lexer.h"

#include "minecpp/lexer/Core.h"
#include "minecpp/lexer/IStreamReader.h"

namespace minecpp::tool::schema_compiler {

enum class Environment
{
   Base,
   String,
   StringEscape,
   PreComment,
   SingleLineComment,
   MultiLineComment,
   FinishMultiLineComment
};

TokenType classify_token(const std::string &token_value, Environment environment)
{
   if (environment == Environment::String)
      return TokenType::String;

   if (token_value == "package")
      return TokenType::KeywordPackage;
   if (token_value == "import")
      return TokenType::KeywordImport;
   if (token_value == "record")
      return TokenType::KeywordRecord;

   return TokenType::Identifier;
}

using Lex = lexer::Types<TokenType, Token, Environment, classify_token>;

// clang-format off

using BaseEnvironment = Lex::FirstMatch<
   Lex::OnCharFlushAndSkip<' '>,
   Lex::OnCharFlushAndSkip<'\t'>,
   Lex::OnChar<'\n', Lex::Sequence<
      Lex::FlushStash,
      Lex::AddCharToken<'\n', TokenType::NewLine>,
      Lex::IncreaseLineNumber
   >>,
   Lex::OnCharFlushAndAddItAsToken<'[', TokenType::LeftSquareBracket>,
   Lex::OnCharFlushAndAddItAsToken<']', TokenType::RightSquareBracket>,
   Lex::OnCharFlushAndAddItAsToken<'{', TokenType::LeftBracket>,
   Lex::OnCharFlushAndAddItAsToken<'}', TokenType::RightBracket>,
   Lex::OnCharFlushAndAddItAsToken<'=', TokenType::EqualSign>,
   Lex::OnCharFlushAndAddItAsToken<':', TokenType::Colon>,
   Lex::OnCharFlushAndAddItAsToken<'.', TokenType::Dot>,
   Lex::OnCharFlushAndAddItAsToken<',', TokenType::Comma>,
   Lex::OnCharFlushAndEnterEnvironment<'"', Environment::String>,
   Lex::OnCharFlushAndEnterEnvironment<'/', Environment::PreComment>,
   Lex::AddCurrentCharToStash
>;

using StringEnvironment = Lex::FirstMatch<
   Lex::OnCharFlushAndEnterEnvironment<'"', Environment::Base>,
   Lex::OnCharEnterEnvironment<'\\', Environment::StringEscape>,
   Lex::AddCurrentCharToStash
>;

using StringEscapeEnvironment = Lex::Sequence<
   Lex::FirstMatch<
      Lex::OnCharAddToStash<'"', '"'>,
      Lex::OnCharAddToStash<'n', '\n'>,
      Lex::OnCharAddToStash<'r', '\r'>,
      Lex::OnCharAddToStash<'t', '\t'>
   >,
   Lex::EnterEnvironment<Environment::String>
>;

using PreCommentEnvironment = Lex::FirstMatch<
   Lex::OnCharEnterEnvironment<'/', Environment::SingleLineComment>,
   Lex::OnCharEnterEnvironment<'*', Environment::MultiLineComment>,
   Lex::Sequence<
      Lex::StepBack,
      Lex::AddToStash<'/'>,
      Lex::EnterEnvironment<Environment::Base>
   >
>;

using SingleLineCommentEnvironment = Lex::FirstMatch<
   Lex::OnChar<'\n', Lex::Sequence<
      Lex::AddCharToken<'\n', TokenType::NewLine>,
      Lex::IncreaseLineNumber,
      Lex::EnterEnvironment<Environment::Base>
   >>,
   Lex::Skip
>;

using MultiLineCommentEnvironment = Lex::FirstMatch<
   Lex::OnCharEnterEnvironment<'*', Environment::FinishMultiLineComment>,
   Lex::OnChar<'\n', Lex::IncreaseLineNumber>,
   Lex::Skip
>;

using FinishMultiLineCommentEnvironment = Lex::FirstMatch<
   Lex::OnCharEnterEnvironment<'/', Environment::Base>,
   Lex::EnterEnvironment<Environment::MultiLineComment>
>;

// clang-format on

std::vector<Token> lex_input(std::istream &input)
{
   minecpp::lexer::IStreamReader reader(input);
   return minecpp::lexer::lex_from<Lex, BaseEnvironment, StringEnvironment, StringEscapeEnvironment,
                                   PreCommentEnvironment, SingleLineCommentEnvironment,
                                   MultiLineCommentEnvironment, FinishMultiLineCommentEnvironment>(reader);
}

}// namespace minecpp::tool::schema_compiler
