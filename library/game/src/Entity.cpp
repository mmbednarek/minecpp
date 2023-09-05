#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::game {

Entity::Entity(entt::registry &registry, game::EntityId id) :
    m_entity(static_cast<entt::entity>(id)),
    m_registry(registry)
{
}

void Entity::serialize_to_proto(proto::entity::Entity *entity) const
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

void Entity::serialize_player_to_proto(proto::entity::PlayerEntity *entity) const
{
   assert(entity);

   entity->set_entity_id(static_cast<mb::u32>(m_entity));

   this->for_each_component([entity](const entt::meta_any &obj) mutable {
      using namespace entt::literals;
      auto serialize = obj.type().func("serialize_player_to_proto"_hs);
      if (serialize) {
         serialize.invoke(obj, entity);
      }
   });
}

void Entity::serialize_to_net(NetworkEntity *net_entity) const
{
   assert(net_entity);

   net_entity->entity_data.entity_id = static_cast<mb::u32>(m_entity);
   net_entity->metadata.entity_id = static_cast<mb::u32>(m_entity);

   this->for_each_component([net_entity](const entt::meta_any &obj) mutable {
     using namespace entt::literals;
     auto serialize = obj.type().func("serialize_to_net"_hs);
     if (serialize) {
        serialize.invoke(obj, net_entity);
     }
   });
}

void Entity::serialize_player_to_net(NetworkPlayer *net_player) const
{
   assert(net_player);

   net_player->player_data.entity_id = static_cast<mb::u32>(m_entity);
   net_player->metadata.entity_id = static_cast<mb::u32>(m_entity);

   this->for_each_component([net_player](const entt::meta_any &obj) mutable {
     using namespace entt::literals;
     auto serialize = obj.type().func("serialize_player_to_net"_hs);
     if (serialize) {
        serialize.invoke(obj, net_player);
     }
   });
}

game::EntityId Entity::id() const
{
   return static_cast<game::EntityId>(m_entity);
}

bool Entity::is_valid() const
{
   return this->m_registry.valid(m_entity);
}

void Entity::on_killed(IWorld &world)
{
   this->for_each_component([this, &world](entt::meta_any &obj) mutable {
      using namespace entt::literals;
      auto on_killed = obj.type().func("on_killed"_hs);
      if (on_killed) {
         on_killed.invoke(obj, &world, this);
      }
   });
}

void Entity::on_attached_to_world(IWorld &world, const math::Vector3 &position, const math::Vector3 &extent)
{
   this->for_each_component([this, &world, &position, &extent](entt::meta_any &obj) mutable {
      using namespace entt::literals;
      auto on_attached_to_world = obj.type().func("on_attached_to_world"_hs);
      if (on_attached_to_world) {
         on_attached_to_world.invoke(obj, &world, this, position, extent);
      }
   });
}

Movement Movement::from_vector3(const math::Vector3 &position)
{
   return {(position * 4096.0).cast<short>()};
}

math::Vector3 Movement::to_vector3() const
{
   return this->movement.cast<double>() / 4096.0;
}

}// namespace minecpp::game
