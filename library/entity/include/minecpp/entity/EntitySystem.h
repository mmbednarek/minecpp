#pragma once

#include <minecpp/game/Entity.h>
#include <minecpp/game/Entt.hpp>
#include <minecpp/game/IEntitySystem.hpp>
#include <minecpp/proto/entity/Entity.pb.h>
#include <optional>
#include <shared_mutex>

namespace minecpp::world {

class IChunkSystem;

}

namespace minecpp::entity {

class EntitySpace;

class EntitySystem final : public game::IEntitySystem
{
 public:
   EntitySystem(world::IChunkSystem &chunk_system);
   ~EntitySystem() override;

   game::Entity create_spatial_entity(math::Vector3 position, math::Vector3 extent) override;
   std::vector<game::EntityId> list_entities_in(math::Vector3 min, math::Vector3 max) override;
   std::optional<game::EntityId> find_nearest_to(math::Vector3 position) override;
   game::Entity entity(game::EntityId id) override;
   void destroy_entity(game::EntityId id) override;
   void detach_entity(game::EntityId id) override;
   std::vector<game::EntityId> list_entities_in_view_distance(math::Vector3 position) override;
   std::vector<game::EntityId> list_entities_intersecting_with(math::Vector3 min, math::Vector3 max) override;
   [[nodiscard]] double view_distance() const override;
   void move_spatial_entity(game::EntityId id, math::Vector3 extend, math::Vector3 old_position,
                            math::Vector3 new_position) override;
   void tick_entities(game::IWorld &world, double delta_time) override;
   void attach_entity(game::IWorld &world, game::EntityId entity_id, const math::Vector3 &position,
                      const math::Vector3 &extent) override;
   void apply_pending_kills();

 private:
   std::mutex m_kill_mtx;
   world::IChunkSystem &m_chunk_system;
   entt::registry m_registry;
   std::unique_ptr<EntitySpace> m_storage;
   std::vector<game::EntityId> m_pending_kills;
   double m_view_distance{16.0};
   double m_min_y{-64.0};
   double m_max_y{1024.0};
};

class IEntityFactory
{
 public:
   virtual ~IEntityFactory() = default;

   virtual game::Entity create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system) = 0;
};

}// namespace minecpp::entity
