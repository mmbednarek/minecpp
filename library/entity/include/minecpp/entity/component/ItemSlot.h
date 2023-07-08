#pragma once

#include "Location.h"

#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

class ItemSlot
{
 public:
   explicit ItemSlot(game::ItemSlot slot);

   void on_attached(game::Entity &entity);
   void on_begin_intersect(game::IWorld &world, game::Entity &entity, game::Entity &other_entity) const;

   void serialize_to_proto(proto::entity::Entity *entity) const;

 private:
   game::ItemSlot m_slot;
   Location::BeginIntersect::OptSink<ItemSlot> m_begin_intersect_sink;
};

}// namespace minecpp::entity::component
