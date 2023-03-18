#pragma once

#include "../Command.h"

namespace minecpp::command::core {

class Spawn : public Command
{
 public:
   static constexpr auto command_return_type = ObjectType::FormattedString;
   static constexpr auto command_name        = "spawn";

   [[nodiscard]] bool is_flag(std::string_view name) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
};

}// namespace minecpp::command::core
