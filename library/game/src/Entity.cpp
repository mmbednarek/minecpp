#include <minecpp/game/Entity.h>

namespace minecpp::game {

Entity::Entity(entt::registry &registry, game::EntityId id) :
    m_entity(static_cast<entt::entity>(id)),
    m_registry(registry)
{
}

void Entity::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   assert(entity);

   entity->set_entity_id(static_cast<mb::u32>(m_entity));

   this->for_each_component([entity](const entt::meta_any &obj) mutable {
      using namespace entt::literals;
      auto serialize = obj.type().func("serialize_to_proto"_hs);
      if (serialize) {
         serialize.invoke(obj, entity);
      }
   });
}

game::EntityId Entity::id() const
{
   return static_cast<game::EntityId>(m_entity);
}

Movement Movement::from_vector3(const math::Vector3 &position)
{
   return {(position * 4096.0).cast<short>()};
}

math::Vector3 Movement::to_vector3() const
{
   return this->movement.cast<double>() / 4096.0;
}

proto::common::v1::Rotation Rotation::to_proto() const
{
   proto::common::v1::Rotation result;
   result.set_yaw(yaw);
   result.set_pitch(pitch);
   return result;
}
}// namespace minecpp::game
