#include <minecpp/command/core/echo.h>
#include <minecpp/command/runtime_context.h>
#include <sstream>

namespace minecpp::command::core {

bool Echo::is_flag(std::string_view name) const
{
   return true;
}

Object::Ptr Echo::run(RuntimeContext &ctx, CommandInput &input) const
{
   std::stringstream ss;
   auto it        = input.arguments.begin();
   const auto end = input.arguments.end();

   if (it == end)
      return {};

   ss << (*it)->to_string();
   std::for_each(it + 1, end, [&ss](Object::Ptr &obj) { ss << ' ' << obj->to_string(); });

   return std::make_shared<StringObject>(ss.str());
}

ObjectType Echo::return_type(RuntimeContext &ctx) const
{
   return command_return_type;
}

}// namespace minecpp::command::core