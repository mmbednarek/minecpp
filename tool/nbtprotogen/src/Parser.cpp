#include "Parser.h"
#include "Error.h"
#include <fmt/core.h>

using minecpp::tool::nbt_idl::Error;
using minecpp::tool::nbt_idl::ErrorType;

#include <fmt/core.h>

namespace Syntax {

Parser::Parser(Lex::TokenReader &reader) :
    reader(reader)
{
}

std::vector<Ast::Node> Parser::parse()
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
         out.emplace_back(parse_syntax_info(Ast::Location(tkn)));
      } break;
      case TokenType::Package: {
         out.emplace_back(parse_package_info(Ast::Location(tkn)));
      } break;
      case TokenType::Message: {
         out.emplace_back(parse_message(Ast::Location(tkn)));
      } break;
      case TokenType::Import: {
         out.emplace_back(parse_import(Ast::Location(tkn)));
      } break;
      default: throw Error(tkn.line, tkn.col, ErrorType::UnexpectedToken, "");
      }
   }

   return out;
}

Ast::SyntaxInfo Parser::parse_syntax_info(Ast::Location loc)
{
   using Lex::TokenType;
   Ast::SyntaxInfo out;
   out.loc = loc;

   auto result = reader.expect(TokenType::EqualSign);

   auto syntax = reader.expect(TokenType::String);
   out.version = syntax.value;

   reader.expect(TokenType::SemiCol);

   return out;
}

Ast::PackageInfo Parser::parse_package_info(Ast::Location loc)
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
         auto tkn = reader.expect(TokenType::Identifier);
         out.package.emplace_back(tkn.value);
      }
      auto tkn = reader.next();
      if (tkn.tt == TokenType::SemiCol) {
         break;
      }
      if (tkn.tt != TokenType::Dot) {
         throw Error(tkn.line, tkn.col, ErrorType::UnexpectedToken, "");
      }
   }

   return out;
}

Ast::Message Parser::parse_message(Ast::Location loc)
{
   using Lex::TokenType;
   Ast::Message out;
   out.loc = loc;

   out.name = reader.expect(TokenType::Identifier).value;

   reader.expect(TokenType::LeftBrace);

   for (;;) {
      auto next = reader.next();
      if (next.tt == TokenType::RightBrace) {
         break;
      }
      reader.back();
      out.attributes.emplace_back(parse_attribute(Ast::Location(next)));
   }

   return out;
}

Ast::Attribute Parser::parse_attribute(Ast::Location loc)
{
   using Lex::TokenType;
   Ast::Attribute out;
   out.loc = loc;

   auto tkn = reader.expect(TokenType::Identifier);
   if (tkn.value == "optional") {
      out.optional = true;
      tkn          = reader.expect(TokenType::Identifier);
   }
   while (tkn.value == "repeated") {
      ++out.repeated;
      tkn = reader.expect(TokenType::Identifier);
   }
   out.type = tkn.value;

   if (tkn.value == "map") {
      reader.expect(TokenType::LeftAngle);

      auto string_token = reader.expect(TokenType::Identifier);
      if (string_token.value != "string")
         throw Error(tkn.line, tkn.col, ErrorType::InvalidMapKey, "");

      reader.expect(TokenType::Comma);

      auto subtype_token = reader.expect(TokenType::Identifier);
      out.subtype        = subtype_token.value;

      reader.expect(TokenType::RightAngle);
   }

   tkn = reader.next();
   while (tkn.tt == TokenType::Dot) {
      out.package.emplace_back(out.type);
      tkn      = reader.expect(TokenType::Identifier);
      out.type = tkn.value;
      tkn      = reader.next();
   }
   reader.back();

   tkn      = reader.expect(TokenType::Identifier);
   out.name = tkn.value;

   reader.expect(TokenType::EqualSign);

   tkn     = reader.expect(TokenType::Integer);
   out.pos = std::stoi(tkn.value);

   // look a head for label
   tkn = reader.next();
   if (tkn.tt == TokenType::LeftSquare) {
      tkn = reader.expect(TokenType::Identifier);
      if (tkn.value == "label" || tkn.value == "json_name") {
         reader.expect(TokenType::EqualSign);

         tkn       = reader.expect(TokenType::String);
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

   reader.expect(TokenType::SemiCol);
   return out;
}

Ast::Import Parser::parse_import(Ast::Location loc)
{
   using Lex::TokenType;
   Ast::Import result;
   result.loc = loc;

   auto res    = reader.expect(TokenType::String);
   result.path = res.value.substr(1, res.value.size() - 2);

   reader.expect(TokenType::SemiCol);
   return result;
}

}// namespace Syntax
