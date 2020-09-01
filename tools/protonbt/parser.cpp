#include "parser.h"

namespace Syntax {

Parser::Parser(Lex::TokenReader &reader) : reader(reader) {
}

result<std::vector<Ast::Node>> Parser::parse() {
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
      default:
         return errorf("[{}:{}] unexpected token \"{}\"", tkn.line, tkn.col, tkn.value);
      }
   }

   return out;
}

result<Ast::SyntaxInfo> Parser::parse_syntax_info(Ast::Location loc) {
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
   auto tkn = res.unwrap();
   out.version = tkn.value;

   if (auto res = reader.expect(TokenType::SemiCol); !res.ok()) {
      return res.err();
   }

   return out;
}

result<Ast::PackageInfo> Parser::parse_package_info(Ast::Location loc) {
   using Lex::TokenType;
   Ast::PackageInfo out;
   out.loc = loc;

   for (;;) {
      auto tkn = tryget(reader.expect(TokenType::Identifier));
      out.package.emplace_back(tkn.value);
      tkn = reader.next();
      if (tkn.tt == TokenType::SemiCol) {
         break;
      }
      if (tkn.tt != TokenType::Dot) {
         return errorf("[{}:{}] unexpected token \"{}\"", tkn.line, tkn.col, tkn.value);
      }
   }

   return out;
}

result<Ast::Message> Parser::parse_message(Ast::Location loc) {
   using Lex::TokenType;
   Ast::Message out;
   out.loc = loc;

   auto res = tryget(reader.expect(TokenType::Identifier));
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
      out.attributes.emplace_back(tryget(parse_attribute(Ast::Location(next))));
   }

   return out;
}

result<Ast::Attribute> Parser::parse_attribute(Ast::Location loc) {
   using Lex::TokenType;
   Ast::Attribute out;
   out.loc = loc;

   auto tkn = tryget(reader.expect(TokenType::Identifier));
   while (tkn.value == "repeated") {
      ++out.repeated;
      tkn = tryget(reader.expect(TokenType::Identifier));
   }
   out.type = tkn.value;

   tkn = tryget(reader.expect(TokenType::Identifier));
   out.name = tkn.value;

   if (auto res = reader.expect(TokenType::EqualSign); !res.ok()) {
      return res.err();
   }

   tkn = tryget(reader.expect(TokenType::Integer));
   out.pos = std::stoi(tkn.value);

   // look a head for label
   tkn = reader.next();
   if (tkn.tt == TokenType::LeftSquare) {
      tkn = tryget(reader.expect(TokenType::Identifier));
      if (tkn.value == "label" || tkn.value == "json_name") {
         if (auto res = reader.expect(TokenType::EqualSign); !res.ok()) {
            return res.err();
         }
         tkn = tryget(reader.expect(TokenType::String));
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

}// namespace Syntax
