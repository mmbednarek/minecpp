#ifndef MINECPP_PARSER_H
#define MINECPP_PARSER_H
#include "ast/ast.h"
#include "result.h"
#include <minecpp/lexer/reader.h>
#include <minecpp/lexer/token.h>
#include <optional>
#include <vector>

namespace minecpp::command {

class CommandManager;

class Parser
{
   lexer::TokenReader m_reader;
   CommandManager &m_command_manager;

 public:
   explicit Parser(const std::vector<lexer::Token> &tokens, CommandManager &command_manager);

   Result<ast::Command> read_command();
   Result<ast::Expression::Ptr> read_expression();

   [[nodiscard]] Result<lexer::Token> expected_token(lexer::TokenType type);
};

}// namespace minecpp::command

#endif//MINECPP_PARSER_H
