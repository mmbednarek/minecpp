#include <minecpp/entity/component/Abilities.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/EntitySystem.h>

namespace minecpp::entity::component {

void Abilities::serialize_to_proto(proto::entity::v1::Entity * /*entity*/) const {}

void Abilities::on_attached(game::Entity &entity)
{
   m_entity_id = entity.id();
}

void Abilities::set_is_flying_enabled(game::IWorld &world, bool enabled)
{
   auto entity = world.entity_system().entity(m_entity_id);
   assert(entity.has_component<Player>());

   auto player_id = entity.component<Player>().id();

   m_abilities.may_fly = enabled;
   world.dispatcher().set_abilities(player_id, m_abilities);
}

const game::Abilities &Abilities::abilities() const
{
   return m_abilities;
}

void Abilities::set_can_instantly_destroy_blocks(game::IWorld &world, bool enabled)
{
   auto entity = world.entity_system().entity(m_entity_id);
   assert(entity.has_component<Player>());

   auto player_id = entity.component<Player>().id();

   m_abilities.may_build = enabled;
   world.dispatcher().set_abilities(player_id, m_abilities);
}

}// namespace minecpp::entity::component
