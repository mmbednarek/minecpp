#pragma once

#include <fmt/core.h>
#include <istream>
#include <string>
#include <vector>

namespace minecpp::tool::schema_compiler {

enum class TokenType
{
   KeywordPackage,
   KeywordImport,
   KeywordRecord,
   KeywordGenerator,
   Identifier,
   String,
   LeftBracket,
   RightBracket,
   LeftSquareBracket,
   RightSquareBracket,
   EqualSign,
   Colon,
   Comma,
   Dot,
   NewLine
};

struct Token
{
   TokenType type;
   std::string value;
   int line;
   int column;
};

std::vector<Token> lex_input(std::istream &input);

}// namespace minecpp::tool::schema_compiler

template<>
struct fmt::formatter<minecpp::tool::schema_compiler::TokenType>
{
   template<typename ParseContext>
   constexpr auto parse(ParseContext &ctx)
   {
      return ctx.begin();
   }

   template<typename FormatContext>
   auto format(const minecpp::tool::schema_compiler::TokenType token_type, FormatContext &ctx)
   {
      using enum minecpp::tool::schema_compiler::TokenType;
      switch (token_type) {
      case KeywordPackage: return fmt::format_to(ctx.out(), "KeywordPackage");
      case KeywordImport: return fmt::format_to(ctx.out(), "KeywordImport");
      case KeywordRecord: return fmt::format_to(ctx.out(), "KeywordRecord");
      case KeywordGenerator: return fmt::format_to(ctx.out(), "KeywordGenerator");
      case Identifier: return fmt::format_to(ctx.out(), "Identifier");
      case String: return fmt::format_to(ctx.out(), "String");
      case LeftBracket: return fmt::format_to(ctx.out(), "LeftBracket");
      case RightBracket: return fmt::format_to(ctx.out(), "RightBracket");
      case LeftSquareBracket: return fmt::format_to(ctx.out(), "LeftSquareBracket");
      case RightSquareBracket: return fmt::format_to(ctx.out(), "RightSquareBracket");
      case EqualSign: return fmt::format_to(ctx.out(), "EqualSign");
      case Colon: return fmt::format_to(ctx.out(), "Colon");
      case Comma: return fmt::format_to(ctx.out(), "Comma");
      case Dot: return fmt::format_to(ctx.out(), "Dot");
      case NewLine: return fmt::format_to(ctx.out(), "NewLine");
      }

      return ctx.out();
   }
};