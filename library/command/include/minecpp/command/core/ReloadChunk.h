#pragma once

#include "../Command.h"
#include <minecpp/game/player/Provider.hpp>

namespace minecpp::command::core {

class ReloadChunk : public Command
{
 public:
   static constexpr auto command_return_type = ObjectType::String;

   explicit ReloadChunk(game::World &world);

   [[nodiscard]] bool is_flag(std::string_view name) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;

 private:
   game::World &m_world;
};

}// namespace minecpp::command::core
