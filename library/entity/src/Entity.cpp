#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/Entity.h>

namespace minecpp::entity {

Entity::Entity(entt::registry &registry, game::EntityId id) :
    m_entity(static_cast<entt::entity>(id)),
    m_registry(registry)
{
}

math::Vector3 Entity::position() const
{
   return m_registry.get<component::Location>(m_entity).position;
}

void Entity::serialize_to_proto(proto::entity::v1::Entity *entity) const {
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

}// namespace minecpp::entity
