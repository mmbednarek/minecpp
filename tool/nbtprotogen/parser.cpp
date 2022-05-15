#include "parser.h"
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
         auto res = parse_syntax_info(Ast::Location(tkn));
         if (!res.ok()) {
            return res.err();
         }
         out.emplace_back(res.unwrap());
      } break;
      case TokenType::Package: {
         auto res = parse_package_info(Ast::Location(tkn));
         if (!res.ok()) {
            return res.err();
         }
         out.emplace_back(res.unwrap());
      } break;
      case TokenType::Message: {
         auto res = parse_message(Ast::Location(tkn));
         if (!res.ok()) {
            return res.err();
         }
         out.emplace_back(res.unwrap());
      } break;
      case TokenType::Import: {
         auto res = parse_import(Ast::Location(tkn));
         if (!res.ok()) {
            return res.err();
         }
         out.emplace_back(res.unwrap());
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

   if (auto res = reader.expect(TokenType::EqualSign); !res.ok()) {
      return res.err();
   }

   auto res = reader.expect(TokenType::String);
   if (!res.ok()) {
      return res.err();
   }
   auto tkn    = res.unwrap();
   out.version = tkn.value;

   if (auto res = reader.expect(TokenType::SemiCol); !res.ok()) {
      return res.err();
   }

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

   if (auto res = reader.expect(TokenType::LeftBrace); !res.ok()) {
      return res.err();
   }

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
   while (tkn.value == "repeated") {
      ++out.repeated;
      tkn = MB_TRY(reader.expect(TokenType::Identifier));
   }
   out.type = tkn.value;

   if (tkn.value == "map") {
      if (auto res = reader.expect(TokenType::LeftAngle); !res.ok()) {
         return res.err();
      }
      auto string_token = MB_TRY(reader.expect(TokenType::Identifier));
      if (string_token.value != "string") {
         return mb::error("only string is supported as a map key");
      }
      if (auto res = reader.expect(TokenType::Comma); !res.ok()) {
         return res.err();
      }
      auto subtype_token = MB_TRY(reader.expect(TokenType::Identifier));
      out.subtype        = subtype_token.value;
      if (auto res = reader.expect(TokenType::RightAngle); !res.ok()) {
         return res.err();
      }
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

   if (auto res = reader.expect(TokenType::EqualSign); !res.ok()) {
      return res.err();
   }

   tkn     = MB_TRY(reader.expect(TokenType::Integer));
   out.pos = std::stoi(tkn.value);

   // look a head for label
   tkn = reader.next();
   if (tkn.tt == TokenType::LeftSquare) {
      tkn = MB_TRY(reader.expect(TokenType::Identifier));
      if (tkn.value == "label" || tkn.value == "json_name") {
         if (auto res = reader.expect(TokenType::EqualSign); !res.ok()) {
            return res.err();
         }
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

   if (auto res = reader.expect(TokenType::SemiCol); !res.ok()) {
      return res.err();
   }
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
