#include "Parser.h"

namespace minecpp::tool::snbt_parser {

Parser::Parser(const std::vector<Token> &tokens) :
    m_reader(tokens)
{
}

nbt::CompoundContent Parser::read_compound()
{
   nbt::CompoundContent result;

   assert_not_end();
   if (m_reader.token_type() == TokenType::RightBrace) {
      m_reader.skip_next();
      return result;
   }

   for (;;) {
      auto label = expect_identifier();
      expect(TokenType::Colon);

      result[label] = read_content();

      if (m_reader.token_type() == TokenType::Comma) {
         m_reader.skip_next();
         continue;
      }

      expect(TokenType::RightBrace);
      break;
   }

   return result;
}

Token Parser::expect(TokenType type)
{
   assert_not_end();

   auto token = m_reader.next();
   if (token.type != type)
      throw std::runtime_error("unexpected token type");

   return token;
}

std::string Parser::expect_identifier()
{
   auto token = m_reader.next();
   if (token.type != TokenType::Identifier && token.type != TokenType::String)
      throw std::runtime_error("unexpected token, expected identifier");

   return token.value;
}

void Parser::assert_not_end()
{
   if (not m_reader.has_next())
      throw std::runtime_error("unexpected end of token stream");
}

nbt::Content Parser::read_content()
{
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
   case TokenType::LeftBrace: return nbt::make_compound(read_compound());
   case TokenType::LeftSquareBracket: return nbt::make_list(read_list());
   default: break;
   }

   throw std::runtime_error("invalid token type");
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
   default: break;
   }
   return nbt::TagId::End;
}

nbt::ListContent Parser::read_list()
{
   if (m_reader.token_type() == TokenType::RightSquareBracket) {
      m_reader.skip_next();
      return nbt::ListContent{.tag_id = nbt::TagId::End, .elements{}};
   }

   nbt::ListContent result{.tag_id = tag_id_by_token_type(m_reader.token_type()), .elements{}};

   for (;;) {
      result.elements.emplace_back(read_content().content);

      if (m_reader.token_type() == TokenType::Comma) {
         m_reader.skip_next();
         continue;
      }

      expect(TokenType::RightSquareBracket);
      break;
   }

   return result;
}

}// namespace minecpp::tool::snbt_parser
