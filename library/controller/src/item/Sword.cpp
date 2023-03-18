#include <minecpp/controller/item/Sword.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Team.h>
#include <minecpp/game/IEntitySystem.hpp>
#include <minecpp/repository/Item.h>

namespace minecpp::controller::item {

void Sword::on_interact(game::IWorld &world, game::ItemId /*item_id*/, game::InteractionType interaction_type,
                        game::EntityId player_entity_id, game::EntityId interaction_entity_id,
                        const math::Vector3f & /*position*/, bool /*is_offhand*/)
{
   using math::Vector3;

   if (interaction_type != game::InteractionType::Attack)
      return;

   auto interaction_entity = world.entity_system().entity(interaction_entity_id);
   if (not interaction_entity.has_component<LocationComponent>())
      return;
   if (not interaction_entity.has_component<HealthComponent>())
      return;

   auto player_entity = world.entity_system().entity(player_entity_id);
   if (not player_entity.has_component<LocationComponent>())
      return;

   auto rotation =
           math::Rotation::from_vector3((interaction_entity.component<LocationComponent>().position() -
                                         player_entity.component<LocationComponent>().position())
                                                .cast<float>());
   rotation.pitch = std::max(rotation.pitch + 0.3f, 0.4f * math::g_pi);

   game::Damage damage{.amount        = 3.0f,
                       .source        = game::DamageSource::PlayerAttack,
                       .source_entity = player_entity_id,
                       .target_entity = interaction_entity_id,
                       .vector        = rotation.vector3<double>()};

   interaction_entity.component<HealthComponent>().apply_damage(world, damage);
}
}// namespace minecpp::controller::item
