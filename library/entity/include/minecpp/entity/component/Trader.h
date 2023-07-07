#pragma once

#include <mb/int.h>
#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

class Trader
{
 public:
   void serialize_to_proto(proto::entity::Entity *entity) const;
   void on_interact(game::IWorld &world, game::Entity &self, game::Entity &other);

 private:
   mb::u32 m_entity_type_id{103};
};

}// namespace minecpp::entity::component