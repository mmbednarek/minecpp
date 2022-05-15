#pragma once
#include <mb/result.h>
#include <string>
#include <variant>
#include <vector>

namespace minecpp::chat {

enum class TokenType
{
   Identifier,
   Integer,
   Float
};

struct Token
{
   TokenType type;
   std::string value;
   int column = 0;
};

using Argument = std::variant<std::string, int, double>;

struct Command
{
   std::string name;
   std::vector<Argument> args;
};

std::vector<Token> lex(std::string_view command);
mb::result<Command> parse(std::vector<Token> &tokens);

}// namespace minecpp::chat
