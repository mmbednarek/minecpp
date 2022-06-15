#include <minecpp/command/core/Echo.h>
#include <minecpp/command/RuntimeContext.h>
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

   auto fmt = std::make_shared<FormattedString>();

   bool first = true;

   for (const auto& obj : input.arguments) {
      if (first) {
         first = false;
      } else {
         fmt->text(format::Color::White, " ");
      }
      if (obj->type() == ObjectType::FormattedString) {
         if (auto *str = cast<FormattedString>(obj); str != nullptr)  {
            std::copy(str->nodes.begin(), str->nodes.end(),
                      std::back_inserter(fmt->nodes));
            continue;
         }
      }
      fmt->text(format::Color::White, obj->to_string());
   }

//   ss << (*it)->to_string();
//   std::for_each(it + 1, end, [&ss](Object::Ptr &obj) {
//      ss << ' ' << obj->to_string();
//
//   });

   return fmt;
}

ObjectType Echo::return_type(RuntimeContext &ctx) const
{
   return command_return_type;
}

}// namespace minecpp::command::core