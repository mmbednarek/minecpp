#pragma once

#include "../Command.h"
#include <minecpp/game/player/Provider.hpp>

namespace minecpp::command::core {

class ReloadChunk : public Command
{
 public:
   static constexpr auto command_return_type = ObjectType::String;

   [[nodiscard]] bool is_flag(std::string_view name) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;
};

}// namespace minecpp::command::core
