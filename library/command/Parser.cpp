#include <minecpp/command/Command.h>
#include <minecpp/command/CommandManager.h>
#include <minecpp/command/Parser.h>

namespace minecpp::command {

Parser::Parser(const std::vector<lexer::Token> &tokens, CommandManager &command_manager) :
    m_reader(tokens),
    m_command_manager(command_manager)
{
}

Result<ast::Command> Parser::read_command()
{
   ast::Command commandAst{};

   auto token = expected_token(lexer::TokenType::Identifier);
   if (token.has_failed()) {
      return std::move(token.err());
   }

   commandAst.name = token->value;

   auto command = m_command_manager.command(commandAst.name);
   if (command == nullptr) {
      return Error(token->line, token->column, "no such command");
   }

   bool read_param_value = false;
   std::string param_name;

   for (;;) {
      if (read_param_value) {
         auto expr = read_expression();
         if (expr.has_failed())
            return std::move(expr.err());
         commandAst.params[param_name] = std::move(expr.get());
         read_param_value              = false;
         continue;
      }

      auto token = m_reader.next();
      if (!token.has_value())
         break;

      if (token->type == lexer::TokenType::RightParen)
         break;

      if (token->type == lexer::TokenType::Identifier && token->value.size() > 1 &&
          token->value.starts_with('-')) {
         if (token->value.starts_with("--")) {
            param_name = token->value.substr(2);
            if (command->is_flag(param_name)) {
               commandAst.flags.insert(param_name);
            } else {
               read_param_value = true;
            }
            continue;
         }

         std::for_each(token->value.begin() + 1, token->value.end() - 1,
                       [&commandAst](const char flag) { commandAst.flags.insert(std::string(1, flag)); });

         param_name = std::string(1, token->value.back());
         if (command->is_flag(param_name)) {
            commandAst.flags.insert(param_name);
         } else {
            read_param_value = true;
         }
         continue;
      }

      m_reader.seek_back();
      auto expr = read_expression();
      if (expr.has_failed())
         return std::move(expr.err());
      commandAst.arguments.push_back(std::move(expr.get()));
   }

   return commandAst;
}

Result<ast::Expression::Ptr> Parser::read_expression()
{
   auto token = m_reader.next();
   if (!token.has_value()) {
      return Error(0, 0, "unexpected end of stream");
   }

   if (token->type == lexer::TokenType::String || token->type == lexer::TokenType::Identifier) {
      return std::make_unique<ast::String>(token->value);
   }

   if (token->type == lexer::TokenType::Int) {
      return std::make_unique<ast::Int>(std::stoi(token->value));
   }

   if (token->type == lexer::TokenType::Variable) {
      return std::make_unique<ast::Variable>(token->value.substr(1));
   }

   if (token->type == lexer::TokenType::LeftParen) {
      auto cmd = read_command();
      if (cmd.has_failed()) {
         return cmd.err();
      }
      return std::make_unique<ast::Command>(std::move(cmd.get()));
   }

   return Error(token->line, token->column, "unexpected token");
}

Result<lexer::Token> Parser::expected_token(lexer::TokenType type)
{
   auto token = m_reader.next();
   if (!token.has_value()) {
      return Error(0, 0, "unexpected end of stream");
   }

   if (token->type != type) {
      return Error(token->line, token->column, "unexpected end of stream");
   }

   return *token;
}

}// namespace minecpp::command
