#pragma once
#include <minecpp/proto/common/Common.pb.h>

namespace minecpp::game {

enum class Mode
{
   Survival,
   Creative,
   Adventure,
   Spectator,
   Hardcore,
};

constexpr proto::common::GameMode write_mode_to_proto(Mode mode)
{
   switch (mode) {
   case Mode::Survival: return proto::common::GameMode::Survival;
   case Mode::Creative: return proto::common::GameMode::Creative;
   case Mode::Adventure: return proto::common::GameMode::Adventure;
   case Mode::Spectator: return proto::common::GameMode::Spectator;
   case Mode::Hardcore: break;
   }
   return proto::common::GameMode::Survival;
}

}// namespace minecpp::game
