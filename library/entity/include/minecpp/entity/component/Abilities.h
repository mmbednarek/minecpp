#pragma once
#include <minecpp/game/Abilities.h>
#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>
#include <minecpp/proto/entity/v1/Entity.pb.h>

namespace minecpp::entity::component {

struct Abilities
{
 public:
   void on_attached(game::Entity &entity);

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
   void set_is_flying_enabled(game::IWorld &world, bool enabled);

   [[nodiscard]] const game::Abilities &abilities() const;

 private:
   game::Abilities m_abilities;
   game::EntityId m_entity_id{};
};

}// namespace minecpp::entity::component
