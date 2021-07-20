#pragma once
#include <minecpp/proto/common/v1/common.pb.h>

namespace minecpp::game {

enum class Mode {
   Survival,
   Creative,
   Adventure,
   Spectator,
   Hardcore,
};

constexpr proto::common::v1::GameMode write_mode_to_proto(Mode mode) {
   switch (mode) {
   case Mode::Survival:
      return proto::common::v1::GameMode::Survival;
   case Mode::Creative:
      return proto::common::v1::GameMode::Creative;
   case Mode::Adventure:
      return proto::common::v1::GameMode::Adventure;
   case Mode::Spectator:
      return proto::common::v1::GameMode::Spectator;
   case Mode::Hardcore: break;
   }
   return proto::common::v1::GameMode::Survival;
}

}
