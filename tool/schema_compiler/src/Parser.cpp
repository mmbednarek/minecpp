#include "Parser.h"

#define RETURN_ERROR(type, token) return make_parser_error(ParserError::type, token->line, token->column)

namespace minecpp::tool::schema_compiler {

Parser::Parser(const std::vector<Token> &tokens) :
    m_token_feed(tokens)
{
}

Result<PackageInfo> Parser::parse_package_info()
{
   auto package_keyword = m_token_feed.expect(TokenType::KeywordPackage);
   if (not package_keyword.has_value())
      return ParserError::MissingPackageKeyword;

   std::vector<std::string> package;

   auto token = m_token_feed.expect(TokenType::Identifier);
   if (not token.has_value())
      RETURN_ERROR(UnexpectedToken, token);

   package.emplace_back(token->value);

   for (;;) {
      token = m_token_feed.next();
      if (not token.has_value())
         RETURN_ERROR(UnexpectedToken, token);

      if (token->type == TokenType::Dot) {
         token = m_token_feed.expect(TokenType::Identifier);
         package.emplace_back(token->value);
         continue;
      } else if (token->type == TokenType::NewLine) {
         break;
      } else {
         RETURN_ERROR(UnexpectedToken, token);
      }
   }

   return PackageInfo(package_keyword->line, package_keyword->column, std::move(package));
}

Result<Document> Parser::parse_document()
{
   this->skip_new_lines();

   auto package = this->parse_package_info();
   if (package.has_failed())
      return package.err();

   Document document(std::move(*package));

   for (;;) {
      this->skip_new_lines();

      auto token = m_token_feed.next();
      if (not token.has_value())
         break;

      if (token->type == TokenType::KeywordImport) {
         m_token_feed.step_back();

         auto import_stmt = this->parse_import();
         if (import_stmt.has_failed())
            return import_stmt.err();

         document.add_import(std::move(*import_stmt));
         continue;
      }

      if (token->type == TokenType::KeywordRecord or token->type == TokenType::LeftSquareBracket) {
         m_token_feed.step_back();

         auto record_stmt = this->parse_record();
         if (record_stmt.has_failed())
            return record_stmt.err();

         document.add_record(std::move(*record_stmt));
         continue;
      }

      RETURN_ERROR(UnexpectedToken, token);
   }

   return document;
}

Result<Import> Parser::parse_import()
{
   auto import_keyword = m_token_feed.expect(TokenType::KeywordPackage);
   if (not import_keyword.has_value())
      RETURN_ERROR(UnexpectedToken, import_keyword);

   auto name = m_token_feed.expect(TokenType::String);
   if (not name.has_value())
      RETURN_ERROR(UnexpectedToken, name);


   return Import(import_keyword->line, import_keyword->column, {name->value});
}

Result<Record> Parser::parse_record()
{
   auto initial_token = m_token_feed.next();
   if (not initial_token.has_value())
      RETURN_ERROR(UnexpectedToken, initial_token);

   AnnotationList annotation_list(initial_token->line, initial_token->column);
   if (initial_token->type == TokenType::LeftSquareBracket) {
      m_token_feed.step_back();

      auto annotation_list_res = this->parse_annotation_list();
      if (annotation_list_res.has_failed())
         return annotation_list_res.err();

      annotation_list = std::move(*annotation_list_res);

      this->skip_new_lines();
      initial_token = m_token_feed.next();
   }

   if (initial_token->type != TokenType::KeywordRecord)
      RETURN_ERROR(UnexpectedToken, initial_token);

   auto token = m_token_feed.expect(TokenType::Identifier);
   if (not token.has_value())
      RETURN_ERROR(UnexpectedToken, token);

   Record record(initial_token->line, initial_token->column, token->value, std::move(annotation_list));

   this->skip_new_lines();

   token = m_token_feed.expect(TokenType::LeftBracket);
   if (not token.has_value())
      RETURN_ERROR(UnexpectedToken, token);

   for (;;) {
      this->skip_new_lines();

      token = m_token_feed.next();
      if (not token.has_value())
         RETURN_ERROR(UnexpectedToken, token);

      if (token->type == TokenType::RightBracket)
         break;

      m_token_feed.step_back();

      auto attribute = this->parse_attribute();
      if (attribute.has_failed())
         RETURN_ERROR(UnexpectedToken, token);

      record.add_attribute(std::move(*attribute));
   }

   return record;
}

Result<AnnotationList> Parser::parse_annotation_list()
{
   auto initial_token = m_token_feed.expect(TokenType::LeftSquareBracket);
   if (not initial_token.has_value())
      RETURN_ERROR(UnexpectedToken, initial_token);

   AnnotationList annotation_list(initial_token->line, initial_token->column);

   for (;;) {
      this->skip_new_lines();

      auto key_token = m_token_feed.next();
      if (not key_token.has_value())
         RETURN_ERROR(UnexpectedToken, key_token);

      if (key_token->type == TokenType::RightSquareBracket)
         break;

      if (key_token->type != TokenType::Identifier)
         RETURN_ERROR(UnexpectedToken, key_token);

      auto token = m_token_feed.next();
      if (not token.has_value())
         RETURN_ERROR(UnexpectedToken, token);

      if (token->type == TokenType::RightSquareBracket) {
         annotation_list.add_annotation(key_token->value, "");
         break;
      }

      if (token->type == TokenType::Comma) {
         annotation_list.add_annotation(key_token->value, "");
         continue;
      }

      if (token->type != TokenType::EqualSign)
         RETURN_ERROR(UnexpectedToken, token);

      auto value_token = m_token_feed.expect(TokenType::String);
      if (not value_token.has_value())
         RETURN_ERROR(UnexpectedToken, value_token);

      annotation_list.add_annotation(key_token->value, value_token->value);

      token = m_token_feed.next();
      if (not token.has_value())
         RETURN_ERROR(UnexpectedToken, token);

      if (token->type == TokenType::Comma)
         continue;
      if (token->type == TokenType::RightSquareBracket)
         break;

      RETURN_ERROR(UnexpectedToken, value_token);
   }

   return annotation_list;
}

Result<Attribute> Parser::parse_attribute()
{
   auto initial_token = m_token_feed.next();
   if (not initial_token.has_value())
      RETURN_ERROR(UnexpectedToken, initial_token);

   AnnotationList annotation_list(initial_token->line, initial_token->column);
   if (initial_token->type == TokenType::LeftSquareBracket) {
      m_token_feed.step_back();

      auto annotation_list_res = this->parse_annotation_list();
      if (annotation_list_res.has_failed())
         return annotation_list_res.err();

      annotation_list = std::move(*annotation_list_res);

      this->skip_new_lines();
      initial_token = m_token_feed.next();
   }

   if (initial_token->type != TokenType::Identifier)
      RETURN_ERROR(UnexpectedToken, initial_token);

   auto token = m_token_feed.expect(TokenType::Colon);
   if (not token.has_value())
      RETURN_ERROR(UnexpectedToken, token);

   auto type = this->parse_type();
   if (type.has_failed())
      return type.err();

   return Attribute(initial_token->line, initial_token->column, std::move(annotation_list), std::move(*type),
                    initial_token->value);
}

Result<Type> Parser::parse_type()
{
   std::vector<std::string> package;

   for (;;) {
      auto token = m_token_feed.expect(TokenType::Identifier);
      if (not token.has_value())
         RETURN_ERROR(UnexpectedToken, token);

      auto dot_token = m_token_feed.next();
      if (not dot_token.has_value())
         RETURN_ERROR(UnexpectedToken, dot_token);

      if (dot_token->type != TokenType::Dot) {
         m_token_feed.step_back();
         m_token_feed.step_back();
         break;
      }

      package.emplace_back(token->value);
   }

   auto name_token = m_token_feed.expect(TokenType::Identifier);
   if (not name_token.has_value())
      RETURN_ERROR(UnexpectedToken, name_token);

   auto token = m_token_feed.next();
   if (not token.has_value())
      RETURN_ERROR(UnexpectedToken, token);

   Type type(name_token->line, name_token->column, std::move(package), name_token->value);

   if (token->type != TokenType::LeftSquareBracket) {
      m_token_feed.step_back();
      return type;
   }

   for (;;) {
      token = m_token_feed.next();
      if (not token.has_value())
         RETURN_ERROR(UnexpectedToken, token);

      if (token->type == TokenType::RightSquareBracket)
         break;

      m_token_feed.step_back();

      auto subtype = this->parse_type();
      if (subtype.has_failed())
         return subtype.err();

      type.add_template_arg(std::move(*subtype));

      token = m_token_feed.next();
      if (not token.has_value())
         RETURN_ERROR(UnexpectedToken, token);

      if (token->type == TokenType::RightSquareBracket)
         break;
      if (token->type != TokenType::Comma)
         RETURN_ERROR(UnexpectedToken, token);
   }

   return type;
}

void Parser::skip_new_lines()
{
   for (;;) {
      auto token = m_token_feed.next();
      if (not token.has_value())
         return;

      if (token->type != TokenType::NewLine)
         break;
   }

   m_token_feed.step_back();
}

ParserError make_parser_error(ParserErrorValue value, int line, int column)
{
   ParserError result(value);
   result.line   = line;
   result.column = column;
   return result;
}

}// namespace minecpp::tool::schema_compiler
