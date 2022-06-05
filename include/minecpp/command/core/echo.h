#ifndef MINECPP_ECHO_H
#define MINECPP_ECHO_H
#include "../command.h"
#include <minecpp/game/notifier.h>

namespace minecpp::command::core {

class Echo : public Command
{
 public:
   static constexpr auto command_return_type = ObjectType::String;

   [[nodiscard]] bool is_flag(std::string_view name) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
};

}// namespace minecpp::command::core

#endif//MINECPP_ECHO_H
