#pragma once
#include <minecpp/game/Entity.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

struct ItemSlot
{
   game::ItemSlot slot;

   void on_attached(game::Entity &entity);
   void on_begin_intersect(game::IWorld &world, game::Entity &entity, game::Entity &other_entity);

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
};

}// namespace minecpp::entity::component
