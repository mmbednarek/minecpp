#include "Parser.h"
#include <fmt/core.h>

namespace Syntax {

Parser::Parser(Lex::TokenReader &reader) :
    reader(reader)
{
}

mb::result<std::vector<Ast::Node>> Parser::parse()
{
   std::vector<Ast::Node> out;
   using Lex::TokenType;

   for (;;) {
      auto tkn = reader.next();
      if (tkn.tt == Lex::TokenType::Eof) {
         break;
      }

      switch (tkn.tt) {
      case TokenType::Syntax: {
         out.emplace_back(MB_TRY(parse_syntax_info(Ast::Location(tkn))));
      } break;
      case TokenType::Package: {
         out.emplace_back(MB_TRY(parse_package_info(Ast::Location(tkn))));
      } break;
      case TokenType::Message: {
         out.emplace_back(MB_TRY(parse_message(Ast::Location(tkn))));
      } break;
      case TokenType::Import: {
         out.emplace_back(MB_TRY(parse_import(Ast::Location(tkn))));
      } break;
      default: return mb::error(fmt::format("[{}:{}] unexpected token \"{}\"", tkn.line, tkn.col, tkn.value));
      }
   }

   return out;
}

mb::result<Ast::SyntaxInfo> Parser::parse_syntax_info(Ast::Location loc)
{
   using Lex::TokenType;
   Ast::SyntaxInfo out;
   out.loc = loc;

   MB_TRY(reader.expect(TokenType::EqualSign));

   auto syntax = MB_TRY(reader.expect(TokenType::String));
   out.version = syntax.value;

   MB_TRY(reader.expect(TokenType::SemiCol));

   return out;
}

mb::result<Ast::PackageInfo> Parser::parse_package_info(Ast::Location loc)
{
   using Lex::TokenType;
   Ast::PackageInfo out;
   out.loc = loc;

   for (;;) {
      auto token = reader.next();
      if (token.tt == TokenType::Message) {
         out.package.emplace_back("message");
      } else {
         reader.back();
         auto tkn = MB_TRY(reader.expect(TokenType::Identifier));
         out.package.emplace_back(tkn.value);
      }
      auto tkn = reader.next();
      if (tkn.tt == TokenType::SemiCol) {
         break;
      }
      if (tkn.tt != TokenType::Dot) {
         return mb::error(fmt::format("[{}:{}] unexpected token \"{}\"", tkn.line, tkn.col, tkn.value));
      }
   }

   return out;
}

mb::result<Ast::Message> Parser::parse_message(Ast::Location loc)
{
   using Lex::TokenType;
   Ast::Message out;
   out.loc = loc;

   auto res = MB_TRY(reader.expect(TokenType::Identifier));
   out.name = res.value;

   MB_TRY(reader.expect(TokenType::LeftBrace));

   for (;;) {
      auto next = reader.next();
      if (next.tt == TokenType::RightBrace) {
         break;
      }
      reader.back();
      out.attributes.emplace_back(MB_TRY(parse_attribute(Ast::Location(next))));
   }

   return out;
}

mb::result<Ast::Attribute> Parser::parse_attribute(Ast::Location loc)
{
   using Lex::TokenType;
   Ast::Attribute out;
   out.loc = loc;

   auto tkn = MB_TRY(reader.expect(TokenType::Identifier));
   if (tkn.value == "optional") {
      out.optional = true;
      tkn          = MB_TRY(reader.expect(TokenType::Identifier));
   }
   while (tkn.value == "repeated") {
      ++out.repeated;
      tkn = MB_TRY(reader.expect(TokenType::Identifier));
   }
   out.type = tkn.value;

   if (tkn.value == "map") {
      MB_TRY(reader.expect(TokenType::LeftAngle));

      auto string_token = MB_TRY(reader.expect(TokenType::Identifier));
      if (string_token.value != "string") {
         return mb::error("only string is supported as a map key");
      }

      MB_TRY(reader.expect(TokenType::Comma));

      auto subtype_token = MB_TRY(reader.expect(TokenType::Identifier));
      out.subtype        = subtype_token.value;

      MB_TRY(reader.expect(TokenType::RightAngle));
   }

   tkn = reader.next();
   while (tkn.tt == TokenType::Dot) {
      out.package.emplace_back(out.type);
      tkn      = MB_TRY(reader.expect(TokenType::Identifier));
      out.type = tkn.value;
      tkn      = reader.next();
   }
   reader.back();

   tkn      = MB_TRY(reader.expect(TokenType::Identifier));
   out.name = tkn.value;

   MB_TRY(reader.expect(TokenType::EqualSign));

   tkn     = MB_TRY(reader.expect(TokenType::Integer));
   out.pos = std::stoi(tkn.value);

   // look a head for label
   tkn = reader.next();
   if (tkn.tt == TokenType::LeftSquare) {
      tkn = MB_TRY(reader.expect(TokenType::Identifier));
      if (tkn.value == "label" || tkn.value == "json_name") {
         MB_TRY(reader.expect(TokenType::EqualSign));

         tkn       = MB_TRY(reader.expect(TokenType::String));
         out.label = tkn.value.substr(1, tkn.value.size() - 2);
      }

      for (;;) {
         tkn = reader.next();
         if (tkn.tt == TokenType::RightSquare || tkn.tt == TokenType::Eof) {
            break;
         }
      }
   } else {
      reader.back();
   }

   MB_TRY(reader.expect(TokenType::SemiCol));
   return out;
}

mb::result<Ast::Import> Parser::parse_import(Ast::Location loc)
{
   using Lex::TokenType;
   Ast::Import result;
   result.loc = loc;

   auto res    = MB_TRY(reader.expect(TokenType::String));
   result.path = res.value.substr(1, res.value.size() - 2);

   MB_TRY(reader.expect(TokenType::SemiCol));
   return result;
}

}// namespace Syntax
