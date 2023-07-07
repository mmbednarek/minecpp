#pragma once
#include <minecpp/game/Abilities.h>
#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>
#include <minecpp/proto/entity/Entity.pb.h>

namespace minecpp::entity::component {

class Abilities
{
 public:
   void on_attached(game::Entity &entity);

   void serialize_to_proto(proto::entity::Entity *entity) const;
   void set_is_flying_enabled(game::IWorld &world, bool enabled);
   void set_can_instantly_destroy_blocks(game::IWorld &world, bool enabled);

   [[nodiscard]] const game::Abilities &abilities() const;

 private:
   game::Abilities m_abilities;
   game::EntityId m_entity_id{};
};

}// namespace minecpp::entity::component
