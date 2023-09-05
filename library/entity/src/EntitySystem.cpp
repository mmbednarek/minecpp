#include "EntitySpace.h"

#include "minecpp/entity/component/DealthScreen.h"
#include "minecpp/entity/component/Health.h"
#include "minecpp/entity/component/Inventory.h"
#include "minecpp/entity/component/ItemSlot.h"
#include "minecpp/entity/component/Location.h"
#include "minecpp/entity/component/Player.h"
#include "minecpp/entity/component/Projectile.h"
#include "minecpp/entity/component/Team.h"
#include "minecpp/entity/component/Ticker.h"
#include "minecpp/entity/component/Totem.h"
#include "minecpp/entity/component/Trader.h"
#include "minecpp/entity/component/UniqueId.h"
#include "minecpp/entity/EntitySystem.h"
#include "minecpp/game/ChunkPosition.h"
#include "minecpp/game/Concepts.hpp"
#include "minecpp/world/IChunkSystem.h"

namespace minecpp::entity {

EntitySystem::EntitySystem(world::IChunkSystem &chunk_system) :
    m_chunk_system(chunk_system),
    m_storage(std::make_unique<EntitySpace>())
{
   game::register_component<component::UniqueId>();
   game::register_component<component::Location>();
   game::register_component<component::Player>();
   game::register_component<component::Health>();
   game::register_component<component::Rotation>();
   game::register_component<component::ItemSlot>();
   game::register_component<component::Projectile>();
   game::register_component<component::Inventory>();
   game::register_component<component::Totem>();
   game::register_component<component::Trader>();
   game::register_component<component::Team>();
   game::register_component<component::DeathScreen>();
}

EntitySystem::~EntitySystem() = default;

game::Entity EntitySystem::create_spatial_entity(math::Vector3 position, math::Vector3 extent)
{
   auto entity_id = m_registry.create();
   auto entity    = this->entity(static_cast<game::EntityId>(entity_id));

   entity.add_component<component::Location>(position, extent);
   m_storage->register_entity(entity.id(), entity.component<component::Location>().logical_position(),
                              extent);

   return entity;
}

std::optional<game::EntityId> EntitySystem::find_nearest_to(math::Vector3 position)
{
   return m_storage->find_nearest(position);
}

std::vector<game::EntityId> EntitySystem::list_entities_in(math::Vector3 min, math::Vector3 max)
{
   return m_storage->list_entities_in(min, max);
}

game::Entity EntitySystem::entity(game::EntityId id)
{
   return {m_registry, id};
}

void EntitySystem::destroy_entity(game::EntityId id)
{
   std::lock_guard lk{m_kill_mtx};
   m_pending_kills.push_back(id);
}

std::vector<game::EntityId> EntitySystem::list_entities_in_view_distance(math::Vector3 position)
{
   const auto block_dist = m_view_distance * 16.0;
   return this->list_entities_in({position.x() - block_dist, m_min_y, position.z() - block_dist},
                                 {position.x() + block_dist, m_max_y, position.z() + block_dist});
}

double EntitySystem::view_distance() const
{
   return m_view_distance;
}

void EntitySystem::tick_entities(game::IWorld &world, double delta_time)
{
   for (auto entity_id : m_registry.view<component::Ticker>()) {
      auto entity = this->entity(static_cast<game::EntityId>(entity_id));
      if (entity.has_component<component::Location>()) {
         // don't tick entity if chunk is empty
         auto state = m_chunk_system.chunk_state_at(
                 game::ChunkPosition::from_position(entity.component<component::Location>().position()));
         if (state != world::ChunkState::COMPLETE)
            continue;
      }

      m_registry.get<component::Ticker>(entity_id).tick(world, entity, delta_time);
   }

   this->apply_pending_kills();
}

void EntitySystem::apply_pending_kills()
{
   assert(m_storage != nullptr);

   std::lock_guard lk{m_kill_mtx};

   for (auto entity_id : m_pending_kills) {
      if (not m_registry.valid(static_cast<entt::entity>(entity_id)))
         continue;

      auto entity = this->entity(entity_id);
      if (entity.has_component<component::Location>()) {
         auto &location = entity.component<component::Location>();
         m_storage->remove_entity(entity_id, location.logical_position(), location.extent());
      }

      m_registry.destroy(static_cast<entt::entity>(entity_id));
   }

   m_pending_kills.clear();
}

void EntitySystem::move_spatial_entity(game::EntityId id, math::Vector3 extend, math::Vector3 old_position,
                                       math::Vector3 new_position)
{
   if (m_storage != nullptr) {
      m_storage->update_position(id, old_position, new_position, extend);
   }
}

std::vector<game::EntityId> EntitySystem::list_entities_intersecting_with(math::Vector3 min,
                                                                          math::Vector3 max)
{
   if (m_storage == nullptr)
      return {};
   return m_storage->list_entities_intersecting_with(min, max);
}

void EntitySystem::detach_entity(game::EntityId id)
{
   assert(m_storage != nullptr);

   auto entity = this->entity(id);
   if (not entity.has_component<component::Location>())
      return;

   const auto &location = entity.component<component::Location>();
   m_storage->remove_entity(id, location.logical_position(), location.extent());

   // TODO: We can attempt removing location component and see what will happen
}

void EntitySystem::attach_entity(game::IWorld &world, game::EntityId entity_id, const math::Vector3 &position,
                                 const math::Vector3 &extent)
{
   assert(m_storage != nullptr);

   auto entity = this->entity(entity_id);
   if (not entity.is_valid())
      return;

   if (not entity.has_component<component::Location>()) {
      entity.add_component<component::Location>(position, extent);
   }

   auto &location = entity.component<component::Location>();
   location.reset_position_and_extent(position, extent);
   m_storage->register_entity(entity_id, location.logical_position(), extent);

   entity.on_attached_to_world(world, position, extent);
}

}// namespace minecpp::entity
