#include "Parser.h"

namespace minecpp::tool::schema_compiler {

using lexer::ParserError;

Parser::Parser(const std::vector<Token> &tokens) :
    m_token_feed(tokens)
{
}

PackageInfo Parser::parse_package_info()
{
   auto package_keyword = m_token_feed.expect(TokenType::KeywordPackage);
   std::vector<std::string> package;

   auto token = m_token_feed.expect(TokenType::Identifier);
   package.emplace_back(token.value);

   for (;;) {
      token = m_token_feed.expect(TokenType::Dot, TokenType::NewLine);
      if (token.type == TokenType::NewLine) {
         break;
      }

      token = m_token_feed.expect(TokenType::Identifier);
      package.emplace_back(token.value);
   }

   return {package_keyword.line, package_keyword.column, std::move(package)};
}

Document Parser::parse_document()
{
   this->skip_new_lines();
   auto generator = this->parse_generator_info();

   this->skip_new_lines();
   auto package = this->parse_package_info();

   Document document(generator.generator(), std::move(package));

   for (;;) {
      this->skip_new_lines();

      if (not m_token_feed.has_next())
         break;

      auto token = m_token_feed.expect(TokenType::KeywordRecord, TokenType::KeywordAlias,
                                       TokenType::LeftSquareBracket);
      m_token_feed.step_back();
      switch (token.type) {
      case TokenType::KeywordRecord: document.add_record(this->parse_record(AnnotationList{})); break;
      case TokenType::KeywordAlias: document.add_alias(this->parse_alias(AnnotationList{})); break;
      case TokenType::LeftSquareBracket: {
         auto annotations = this->parse_annotation_list();
         this->skip_new_lines();
         token = m_token_feed.expect(TokenType::KeywordRecord, TokenType::KeywordAlias);
         m_token_feed.step_back();
         switch (token.type) {
         case TokenType::KeywordRecord:
            document.add_record(this->parse_record(std::move(annotations)));
            break;
         case TokenType::KeywordAlias: document.add_alias(this->parse_alias(std::move(annotations))); break;
         default: break;
         }
         break;
      }
      default: break;
      }
   }

   return document;
}

GeneratorInfo Parser::parse_generator_info()
{
   auto generator_keyword = m_token_feed.expect(TokenType::KeywordGenerator);
   m_token_feed.expect(TokenType::EqualSign);
   auto name = m_token_feed.expect(TokenType::String);
   return {generator_keyword.line, generator_keyword.column, name.value};
}

Import Parser::parse_import()
{
   auto import_keyword = m_token_feed.expect(TokenType::KeywordPackage);
   auto name           = m_token_feed.expect(TokenType::String);
   return {import_keyword.line, import_keyword.column, {name.value}};
}

Record Parser::parse_record(AnnotationList annotations)
{
   auto initial_token = m_token_feed.expect(TokenType::KeywordRecord);
   auto token         = m_token_feed.expect(TokenType::Identifier);
   Record record(initial_token.line, initial_token.column, token.value, std::move(annotations));

   this->skip_new_lines();

   m_token_feed.expect(TokenType::LeftBracket);
   for (;;) {
      this->skip_new_lines();

      token = m_token_feed.next();
      if (token.type == TokenType::RightBracket)
         break;

      m_token_feed.step_back();
      record.add_attribute(this->parse_attribute());
   }

   return record;
}

AnnotationList Parser::parse_annotation_list()
{
   auto initial_token = m_token_feed.expect(TokenType::LeftSquareBracket);
   AnnotationList annotation_list(initial_token.line, initial_token.column);

   for (;;) {
      this->skip_new_lines();

      auto key_token = m_token_feed.expect(TokenType::RightSquareBracket, TokenType::Identifier);
      if (key_token.type == TokenType::RightSquareBracket)
         break;

      auto token = m_token_feed.expect(TokenType::RightSquareBracket, TokenType::Comma, TokenType::EqualSign);
      if (token.type == TokenType::RightSquareBracket) {
         annotation_list.add_annotation(key_token.value, "");
         break;
      }

      if (token.type == TokenType::Comma) {
         annotation_list.add_annotation(key_token.value, "");
         continue;
      }

      auto value_token = m_token_feed.expect(TokenType::String, TokenType::Identifier);
      annotation_list.add_annotation(key_token.value, value_token.value);

      this->skip_new_lines();

      token = m_token_feed.expect(TokenType::Comma, TokenType::RightSquareBracket);
      if (token.type == TokenType::Comma)
         continue;
      if (token.type == TokenType::RightSquareBracket)
         break;
   }

   return annotation_list;
}

Attribute Parser::parse_attribute()
{
   auto initial_token = m_token_feed.expect(TokenType::LeftSquareBracket, TokenType::Identifier,
                                            TokenType::KeywordGenerator);
   AnnotationList annotation_list(initial_token.line, initial_token.column);
   if (initial_token.type == TokenType::LeftSquareBracket) {
      m_token_feed.step_back();

      annotation_list = this->parse_annotation_list();

      this->skip_new_lines();
      initial_token = m_token_feed.expect(TokenType::Identifier, TokenType::KeywordGenerator);
   }

   auto token = m_token_feed.expect(TokenType::Colon);
   auto type  = this->parse_type();

   return {initial_token.line, initial_token.column, std::move(annotation_list), std::move(type),
           initial_token.value};
}

Type Parser::parse_type()
{
   std::vector<std::string> package;

   for (;;) {
      auto token     = m_token_feed.expect(TokenType::Identifier);
      auto dot_token = m_token_feed.next();
      if (dot_token.type != TokenType::Dot) {
         m_token_feed.step_back();
         m_token_feed.step_back();
         break;
      }

      package.emplace_back(token.value);
   }

   auto name_token = m_token_feed.expect(TokenType::Identifier);
   Type type(name_token.line, name_token.column, std::move(package), name_token.value);

   auto token = m_token_feed.next();
   if (token.type != TokenType::LeftSquareBracket) {
      m_token_feed.step_back();
      return type;
   }

   for (;;) {
      token = m_token_feed.next();
      if (token.type == TokenType::RightSquareBracket)
         break;

      m_token_feed.step_back();

      this->skip_new_lines();
      type.add_template_arg(this->parse_type());

      this->skip_new_lines();
      token = m_token_feed.expect(TokenType::RightSquareBracket, TokenType::Comma);
      if (token.type == TokenType::RightSquareBracket)
         break;
   }

   return type;
}

void Parser::skip_new_lines()
{
   for (;;) {
      auto token = m_token_feed.next_opt();
      if (not token.has_value())
         return;

      if (token->type != TokenType::NewLine)
         break;
   }

   m_token_feed.step_back();
}

Alias Parser::parse_alias(AnnotationList annotations)
{
   auto base_token = m_token_feed.expect(TokenType::KeywordAlias);
   auto alias_name = m_token_feed.expect(TokenType::Identifier);
   m_token_feed.expect(TokenType::EqualSign);
   auto aliased_type = this->parse_type();
   return {base_token.line, base_token.column, alias_name.value, std::move(annotations),
           std::move(aliased_type)};
}

}// namespace minecpp::tool::schema_compiler
