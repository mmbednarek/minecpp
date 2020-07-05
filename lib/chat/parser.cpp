#include "parser.h"

namespace Chat {

static bool is_whitespace(char c) {
   switch (c) {
   case ' ':
   case '\n':
   case '\r':
   case '\t':
      return true;
   default:
      break;
   }
   return false;
}

static TokenType deduce_type(std::string_view value) {
   bool numeric = true;
   int dots = 0;
   for (const auto &ch : value) {
      if ((ch < '0' || ch > '9') && ch != '.') {
         numeric = false;
      }

      if (ch == '.') {
         ++dots;
      }
   }

   if (numeric && dots == 1) {
      return TokenType::Float;
   }
   if (numeric) {
      return TokenType::Integer;
   }

   return TokenType::Identifier;
}

std::vector<Token> lex(std::string_view command) {
   std::vector<Token> result;

   Token t;
   for (const auto &ch : command) {
      if (is_whitespace(ch)) {
         if (!t.value.empty()) {
            t.type = deduce_type(t.value);
            result.emplace_back(t);
            t = Token{};
         }
         continue;
      }
      t.value.push_back(ch);
   }
   if (!t.value.empty()) {
      t.type = deduce_type(t.value);
      result.emplace_back(t);
   }

   return result;
}

ParsingResult parse(std::vector<Token> &tokens) {
   if (tokens.empty()) {
      return "no tokens provided";
   }
   if (tokens[0].type != TokenType::Identifier) {
      return "command name must be an identifier";
   }

   Command result{
       .name = tokens[0].value,
   };

   if (tokens.size() == 1) {
      return result;
   }

   for (std::size_t i = 1; i < tokens.size(); ++i) {
      switch (tokens[i].type) {
      case TokenType::Identifier:
         result.args.emplace_back(tokens[i].value);
         break;
      case TokenType::Integer:
         result.args.emplace_back(std::stoi(tokens[i].value));
         break;
      case TokenType::Float:
         result.args.emplace_back(std::stod(tokens[i].value));
         break;
      }
   }

   return result;
}

} // namespace Chat
