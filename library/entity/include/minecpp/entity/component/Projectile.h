#pragma once

#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

class Projectile
{
 public:
   void on_attached(game::Entity &entity);

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
   void on_begin_intersect(game::IWorld &world, game::Entity &entity, game::Entity &other_entity);

 private:
   int m_entity_type_id{3};
};

}// namespace minecpp::entity::component