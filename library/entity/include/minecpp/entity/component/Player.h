#pragma once
#include <minecpp/game/Game.h>
#include <string>

namespace minecpp::entity::component {

struct Player
{
   game::PlayerId id{};
   std::string name;

   void serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const;
};

}// namespace minecpp::entity::component
