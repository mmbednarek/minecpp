#include "Parser.h"

namespace minecpp::tool::snbt_parser {

Parser::Parser(const std::vector<Token> &tokens) :
    m_reader(tokens)
{
}

mb::result<nbt::CompoundContent> Parser::read_compound()
{
   minecpp::nbt::CompoundContent result;
   MB_TRY(assert_not_end());
   if (m_reader.token_type() == TokenType::RightBrace) {
      m_reader.skip_next();
      return result;
   }

   for (;;) {
      auto label = MB_TRY(expect_identifier());
      MB_TRY(expect(TokenType::Colon));

      auto content  = MB_TRY(read_content());
      result[label] = content;

      if (m_reader.token_type() == TokenType::Comma) {
         m_reader.skip_next();
         continue;
      }

      MB_TRY(expect(TokenType::RightBrace));
      break;
   }

   return result;
}

mb::result<Token> Parser::expect(TokenType type)
{
   MB_TRY(assert_not_end());

   auto token = m_reader.next();
   if (token.type != type)
      return mb::error("unexpected token type");

   return token;
}

mb::result<std::string> Parser::expect_identifier()
{
   MB_TRY(assert_not_end());

   auto token = m_reader.next();
   if (token.type != TokenType::Identifier && token.type != TokenType::String)
      return mb::error("unexpected token, expected identifier");

   return std::string(token.value);
}

mb::emptyres Parser::assert_not_end()
{
   if (!m_reader.has_next())
      return mb::error("unexpected end of token stream");
   return mb::ok;
}

mb::result<nbt::Content> Parser::read_content()
{
   MB_TRY(assert_not_end());

   auto token = m_reader.next();

   switch (token.type) {
   case TokenType::String: return nbt::make_string(std::string(token.value));
   case TokenType::Byte:
      return nbt::make_byte(static_cast<int8_t>(std::stoi(token.value.substr(0, token.value.size() - 1))));
   case TokenType::Short:
      return nbt::make_short(static_cast<int16_t>(std::stoi(token.value.substr(0, token.value.size() - 1))));
   case TokenType::Int:
      if (token.value.back() >= '0' && token.value.back() <= '9')
         return nbt::make_int(std::stoi(token.value));
      return nbt::make_int(std::stoi(token.value.substr(0, token.value.size() - 1)));
   case TokenType::Long: return nbt::make_long(std::stoll(token.value.substr(0, token.value.size() - 1)));
   case TokenType::Float: return nbt::make_float(std::stof(token.value.substr(0, token.value.size() - 1)));
   case TokenType::Double: return nbt::make_double(std::stod(token.value.substr(0, token.value.size() - 1)));
   case TokenType::LeftBrace: return nbt::make_compound(MB_TRY(read_compound()));
   case TokenType::LeftSquareBracket: return nbt::make_list(MB_TRY(read_list()));
   }

   return mb::error("invalid token type");
}

static nbt::TagId tag_id_by_token_type(TokenType type)
{
   switch (type) {
   case TokenType::String: return nbt::TagId::String;
   case TokenType::Byte: return nbt::TagId::Byte;
   case TokenType::Short: return nbt::TagId::Short;
   case TokenType::Int: return nbt::TagId::Int;
   case TokenType::Long: return nbt::TagId::Long;
   case TokenType::Float: return nbt::TagId::Float;
   case TokenType::Double: return nbt::TagId::Double;
   case TokenType::LeftBrace: return nbt::TagId::Compound;
   case TokenType::LeftSquareBracket: return nbt::TagId::List;
   }
   return nbt::TagId::End;
}

mb::result<nbt::ListContent> Parser::read_list()
{
   MB_TRY(assert_not_end());
   if (m_reader.token_type() == TokenType::RightSquareBracket) {
      m_reader.skip_next();
      return nbt::ListContent{
              .tag_id = nbt::TagId::End,
      };
   }

   nbt::ListContent result{
           .tag_id = tag_id_by_token_type(m_reader.token_type()),
   };

   for (;;) {
      result.elements.emplace_back(MB_TRY(read_content()).content);

      if (m_reader.token_type() == TokenType::Comma) {
         m_reader.skip_next();
         continue;
      }

      MB_TRY(expect(TokenType::RightSquareBracket));
      break;
   }

   return result;
}

}// namespace minecpp::tool::snbt_parser
