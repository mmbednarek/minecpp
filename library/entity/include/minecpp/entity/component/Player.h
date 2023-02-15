#pragma once
#include <minecpp/game/Game.h>

namespace minecpp::entity::component {

struct Player
{
   game::PlayerId id{};

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
};

}// namespace minecpp::entity::component
