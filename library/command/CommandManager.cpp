#include <minecpp/command/Command.h>
#include <minecpp/command/CommandManager.h>
#include <minecpp/command/Parser.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/lexer/Lexer.h>
#include <minecpp/lexer/Reader.h>

namespace minecpp::command {

Command *CommandManager::command(const std::string &name) const
{
   if (!m_commands.contains(name))
      return nullptr;
   return m_commands.at(name).get();
}

std::optional<Error> CommandManager::evaluate(RuntimeContext &ctx, std::string_view value)
{
   minecpp::lexer::StringReader reader{value};
   minecpp::lexer::Lexer lex(reader);

   auto tokens = lex.lex();
   Parser parser(tokens, *this);

   auto ast = parser.read_command();
   if (ast.has_failed()) {
      return std::move(ast.err());
   }

   auto result = ast->execute(ctx);
   if (result != nullptr) {
      ctx.out().write(result);
   }
   return std::nullopt;
}

}// namespace minecpp::command