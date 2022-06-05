#ifndef MINECPP_COMMAND_MANAGER_H
#define MINECPP_COMMAND_MANAGER_H
#include "result.h"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace minecpp::command {

class Command;
class RuntimeContext;

class CommandManager
{
   std::unordered_map<std::string, std::unique_ptr<Command>> m_commands;

 public:
   [[nodiscard]] Command *command(const std::string &name) const;

   template<typename TCommand, typename... TArgs>
   void register_command(const std::string &name, TArgs &&...args)
   {
      m_commands[name] = std::make_unique<TCommand>(std::forward<TArgs>(args)...);
   }

   std::optional<Error> evaluate(RuntimeContext &ctx, std::string_view value);
};

}// namespace minecpp::command

#endif//MINECPP_COMMAND_MANAGER_H
